/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_infos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:22:25 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/10 14:49:36 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_print_infos(struct stat infos, char *path, char *name, int *tab)
{
	char			*user;
	char			*grp;
	char			*permi;

	if (!(user = ls_get_user(infos)))
		return ;
	if (!(grp = ls_get_group(infos)))
		return ;
	permi = ls_permission(infos);
	ft_putstr(permi);
	ft_putnchar(' ', tab[1] - ft_nblen(infos.st_nlink) + 2);
	ft_putnbr(infos.st_nlink);
	ft_mprintf("ss", " ", user, NULL);
	ft_putnchar(' ', tab[2] - ft_strlen(user));
	ft_putstr(grp);
	ft_putnchar(' ', tab[3] - ft_strlen(grp));
	ls_size_major_minor(infos, tab);
	ls_get_date(infos);
	ft_mprintf("ss", " ", name, NULL);
	if ((infos.st_mode & S_IFMT) == S_IFLNK)
		ls_symb_link(path, infos);
	ft_putbn();
	ft_strdel(&permi);
	ft_strdbldel(&user, &grp);
}

void		ls_symb_link(char *path, struct stat infos)
{
	char *rslt;

	if (!(rslt = ft_strnew(infos.st_size)))
		return ;
	if (!infos.st_size)
		infos.st_size = 5;
	if ((infos.st_mode & S_IFMT) == S_IFLNK)
		readlink(path, rslt, infos.st_size);
	ft_putstr(" -> ");
	ft_putstr(rslt);
	ft_strdel(&rslt);
}

void		ls_dir_link(char *path)
{
	struct passwd	*user;
	struct group	*grp;
	struct stat		infos;
	char			*permi;

	if (lstat(path, &infos) != 0)
		return ;
	if (!(user = getpwuid(infos.st_uid)))
		return ;
	if (!(grp = getgrgid(infos.st_gid)))
		return ;
	permi = ls_permission(infos);
	ft_mprintf("ss", permi, "  ", NULL);
	ft_putnbr(infos.st_nlink);
	ft_mprintf("ss", " ", user->pw_name, NULL);
	ft_mprintf("sss", "  ", grp->gr_name, "  ");
	ft_mprintf("ds", (void *)infos.st_size, " ", NULL);
	ls_get_date(infos);
	ft_mprintf("ss", " ", path, NULL);
	if ((infos.st_mode & S_IFMT) == S_IFLNK)
		ls_symb_link(path, infos);
	ft_putbn();
	ft_strdel(&permi);
}

void		ls_get_date(struct stat infos)
{
	char	*year;

	year = NULL;
	if (!(year = ft_strsub(ctime(&infos.st_mtime), 20, 4)))
		return ;
	if ((time(NULL) - infos.st_mtime) > SIX_MONTH)
		ft_mprintf("sss", ft_strcut(ctime(&infos.st_mtime), 4, 11), " ",
		year);
	else
		ft_putstr(ft_strcut(ctime(&infos.st_mtime), 4, 16));
	ft_strdel(&year);
}

void		ls_size_major_minor(struct stat infos, int *tab)
{
	if (((infos.st_mode & S_IFMT) == S_IFCHR) ||
	((infos.st_mode & S_IFMT) == S_IFBLK))
	{
		ft_putnchar(' ', tab[5] - ft_nblen(major(infos.st_rdev)) + 3);
		ft_putnbr(major(infos.st_rdev));
		ft_putchar(',');
		ft_putnchar(' ', tab[6] - ft_nblen(minor(infos.st_rdev)) + 1);
		ft_putnbr(minor(infos.st_rdev));
		ft_putchar(' ');
	}
	else
	{
		if (tab[5] || tab[6])
			ft_putnchar(' ', tab[5] + tab[6] + 2);
		ft_putnchar(' ', tab[4] - ft_nblen(infos.st_size));
		ft_mprintf("ds", (void *)infos.st_size, " ", NULL);
	}
}

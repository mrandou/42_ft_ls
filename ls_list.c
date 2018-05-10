/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:52:38 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/10 12:00:39 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_list(t_list *list, char *npath)
{
	struct stat	infos;
	char		*path;
	int			*tab;

	path = NULL;
	if (!(tab = ls_links_and_blanks(list, npath)))
		return ;
	if (list)
		ft_putmthings("total ", NULL, NULL, tab[0]);
	while (list)
	{
		if (!(path = ft_strmjoin(npath, "/", list->content)))
			return ;
		lstat(path, &infos);
		if (ls_error(errno, path) == -1)
		{
			ft_memdel((void *)&tab);
			return ;
		}
		ls_print_infos(infos, path, list->content, tab);
		ft_strdel(&path);
		list = list->next;
	}
	ls_lstfree(list);
	ft_memdel((void *)&tab);
}

void		ls_print_infos(struct stat infos, char *path, char *name, int *tab)
{
	char			*user;
	char			*grp;
	char			*permi;
	char			*year;

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
	if (!(year = ft_strsub(ctime(&infos.st_mtime), 20, 4)))
		return ;
	if ((time(NULL) - infos.st_mtime) > SIX_MONTH)
		ft_mprintf("sss", ft_strcut(ctime(&infos.st_mtime), 4, 11), " ",
		year);
	else
		ft_putstr(ft_strcut(ctime(&infos.st_mtime), 4, 16));
	ft_mprintf("ss", " ", name, NULL);
	if ((infos.st_mode & S_IFMT) == S_IFLNK)
		ls_symb_link(path, infos);
	ft_putbn();
	ft_strdel(&permi);
	ft_strdel(&year);
	ft_strdel(&user);
	ft_strdel(&grp);
}

void	ls_size_major_minor(struct stat infos, int *tab)
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

int		*ls_links_and_blanks(t_list *list, char *path)
{
	struct	stat 			infos;
	char					*tmp;
	int						*tab;
	int						i;

	if (!(tab = ft_memalloc(sizeof(int *) + 9)))
		return (NULL);
	i = 0;
	while (i < 7)
		tab[i++] = 0;
	while (list)
	{
		if (!(tmp = ft_strmjoin(path, "/", list->content)))
			return (NULL);
		if (lstat(tmp, &infos) != 0)
		{
			ft_strdel(&tmp);
			ft_memdel((void *)&tab);
			return (NULL);
		}
		if (!(tab = ls_blanks(infos, tab)))
		{
			ft_strdel(&tmp);
			ft_memdel((void *)&tab);
			return (NULL);
		}
		tab[0] = tab[0] + infos.st_blocks;
		ft_strdel(&tmp);
		list = list->next;
	}
	return (tab);
}

int			*ls_blanks(struct stat infos, int *tab)
{
	char			*uid_name;
	char			*gid_name;

	if (!(uid_name = ls_get_user(infos)))
		return (NULL);
	if (!(gid_name = ls_get_group(infos)))
		return (NULL);
	if (tab[1] < ft_nblen(infos.st_nlink))
		tab[1] = ft_nblen(infos.st_nlink);
	if (tab[2] < ((int)ft_strlen(uid_name) + 2))
		tab[2] = ((int)ft_strlen(uid_name) + 2);
	if (tab[3] < ((int)ft_strlen(gid_name)))
		tab[3] = ((int)ft_strlen(gid_name));
	if (tab[4] < ft_nblen(infos.st_size) + 2)
		tab[4] = ft_nblen(infos.st_size) + 2;
	if (((infos.st_mode & S_IFMT) == S_IFCHR) ||
	((infos.st_mode & S_IFMT) == S_IFBLK))
	{
		if (tab[5] < ft_nblen(major(infos.st_rdev) + 3))
			tab[5] = ft_nblen(major(infos.st_rdev) + 3);
		if (tab[6] < ft_nblen(minor(infos.st_rdev) + 1))
			tab[6] = ft_nblen(minor(infos.st_rdev)) + 1;
	}
	ft_strdel(&uid_name);
	ft_strdel(&gid_name);
	return (tab);
}

char		*ls_get_user(struct stat infos)
{
	struct passwd	*user;
	char			*uid_name;

	uid_name = NULL;
	if (!(user = getpwuid(infos.st_uid)))
	{
		if (!(uid_name = ft_itoa(infos.st_uid)))
			return (NULL);
	}
	else
		if (!(uid_name = ft_strdup(user->pw_name)))
			return (NULL);
	return (uid_name);
}

char		*ls_get_group(struct stat infos)
{
	struct group	*grp;
	char			*gid_name;

	gid_name = NULL;
	if (!(grp = getgrgid(infos.st_gid)))
	{
		if (!(gid_name = ft_itoa(infos.st_gid)))
			return (NULL);
	}
	else
		if (!(gid_name = ft_strdup(grp->gr_name)))
			return (NULL);
	return (gid_name);
}

// /private/etc/path.d
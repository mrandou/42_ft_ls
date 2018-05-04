/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_infos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:21:53 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/04 14:21:02 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ls_permission(struct stat infos)
{
	char *permission;

	if (!(permission = ft_strdup("----------")))
		return (NULL);
	if (infos.st_mode & S_IRUSR)
		permission[1] = 'r';
	if (infos.st_mode & S_IWUSR)
		permission[2] = 'w';
	if (infos.st_mode & S_IXUSR)
		permission[3] = 'x';
	if (infos.st_mode & S_IRGRP)
		permission[4] = 'r';
	if (infos.st_mode & S_IWGRP)
		permission[5] = 'w';
	if (infos.st_mode & S_IXGRP)
		permission[6] = 'x';
	if (infos.st_mode & S_IROTH)
		permission[7] = 'r';
	if (infos.st_mode & S_IWOTH)
		permission[8] = 'w';
	if (infos.st_mode & S_IXOTH)
		permission[9] = 'x';
	permission[0] = ls_get_type(infos);
	permission = ls_sticky_and_sgid(infos, permission);
	return (permission);
}

char		*ls_sticky_and_sgid(struct stat infos, char *permission)
{
	if (infos.st_mode & S_ISUID)
		permission[3] = 'S';
	if (infos.st_mode & S_ISGID)
		permission[6] = 'S';
	if (infos.st_mode & S_ISVTX)
		permission[9] = 'T';
	if ((infos.st_mode & S_ISUID) && (infos.st_mode & S_IXUSR))
		permission[3] = 's';
	if ((infos.st_mode & S_ISGID)  && (infos.st_mode & S_IXGRP))
		permission[6] = 's';
	if (infos.st_mode & S_ISVTX  && (infos.st_mode & S_IXOTH))
		permission[9] = 't';
	return (permission);
}

char		ls_get_type(struct stat infos)
{
	char type;

	type = '?';
	if ((infos.st_mode & S_IFMT) == S_IFLNK)
		type = 'l';
	if ((infos.st_mode & S_IFMT) == S_IFREG)
		type = '-';
	if ((infos.st_mode & S_IFMT) == S_IFSOCK)
		type = 's';
	if ((infos.st_mode & S_IFMT) == S_IFIFO)
		type = 'p';
	if ((infos.st_mode & S_IFMT) == S_IFDIR)
		type = 'd';
	if ((infos.st_mode & S_IFMT) == S_IFCHR)
		type = 'c';
	if ((infos.st_mode & S_IFMT) == S_IFBLK)
		type = 'b';
	return (type);
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

void ls_dir_link(char *path)
{
	struct passwd *user;
	struct group *grp;
	struct stat infos;
	char *year;
	char *permi;

	if (lstat(path, &infos) != 0)
		return;
	if (!(user = getpwuid(infos.st_uid)))
		return;
	if (!(grp = getgrgid(infos.st_gid)))
		return;
	permi = ls_permission(infos);
	ft_mprintf("ss", permi, "  ", NULL);
	ft_putnbr(infos.st_nlink);
	ft_mprintf("ss", " ", user->pw_name, NULL);
	ft_mprintf("sss", "  ", grp->gr_name, "  ");
	ft_mprintf("ds", (void *)infos.st_size, " ", NULL);
	if (!(year = ft_strsub(ctime(&infos.st_mtime), 20, 4)))
		return;
	if ((time(NULL) - infos.st_mtime) > SIX_MONTH)
		ft_mprintf("sss", ft_strcut(ctime(&infos.st_mtime), 4, 11), " ",
				   year);
	else
		ft_putstr(ft_strcut(ctime(&infos.st_mtime), 4, 16));
	ft_mprintf("ss", " ", path, NULL);
	if ((infos.st_mode & S_IFMT) == S_IFLNK)
		ls_symb_link(path, infos);
	ft_putbn();
	ft_strdel(&permi);
	ft_strdel(&year);
}
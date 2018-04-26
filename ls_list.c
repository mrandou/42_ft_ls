/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:52:38 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/26 18:31:14 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_list(t_list *list, char *path_name) //pointeur sur fonction ? stat <-> lstat
{
	struct stat infos;
	char *path;
	int *tab;

	tab = ls_links_and_blanks(list, path_name);
	if (list)
	{
		ft_putstr("total ");
		ft_putnbr(tab[0]);
		ft_putbn();
	}
	while (list)
	{
		if (!(path = ft_strjoin(path_name, "/")))
			return ;
		if (!(path = ft_strjoin(path, list->content)))
			return ;
		lstat(path, &infos);
		ls_error(errno, path);
		ls_print_infos(infos, list->content, tab);
		list = list->next;
	}
}

void		ls_print_infos(struct stat infos, char *name, int *tab)
{
	struct passwd	*user;
	struct group	*grp;

	user = getpwuid(infos.st_uid);
	grp = getgrgid(infos.st_gid);
	ft_putstr(ls_permission(infos));
	ft_putnchar(' ', tab[1] - ft_nblen(infos.st_nlink));
	ft_putnbr(infos.st_nlink);
	ft_putstr("  ");
	ft_putstr(user->pw_name);
	ft_putstr(grp->gr_name);
	ft_putnbr(infos.st_size);
	ft_putstr(ft_strcut(ctime(&infos.st_mtime), 4, 16));
	ft_putstr(name);
	ft_putbn();
}

int		*ls_links_and_blanks(t_list *list, char *path)
{
	int			*tab;
	struct	stat infos;
	char		*tmp;

	if (!(tab = (int *)malloc(sizeof(int)))) // ?
		return (NULL);
	tab[0] = 0;
	tab[1] = 2;
	while (list)
	{
		if (!(tmp = ft_strjoin(path, "/")))
			return (0);
	  if (!(tmp = ft_strjoin(tmp, list->content)))
			return (0);
		lstat(tmp, &infos);
		tab[0] = tab[0] + infos.st_blocks;
		if (tab[1] < (ft_nblen(infos.st_nlink) + 2))
			tab[1] = 2 + ft_nblen(infos.st_nlink);
		/*if (tab[2] < (ft_strlen(infos.) + 2))
			tab[2] = 2 + ft_nblen(infos.st_nlink);*/
		ft_strdel(&tmp);
		list = list->next;
	}
	return (tab);
}

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

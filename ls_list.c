/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:52:38 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/10 14:50:39 by mrandou          ###   ########.fr       */
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

int		*ls_links_and_blanks(t_list *list, char *path)
{
	char	*tmp;
	int		*tab;
	int		i;

	if (!(tab = ft_memalloc(sizeof(int *) + 9)))
		return (NULL);
	i = 0;
	while (i < 7)
		tab[i++] = 0;
	while (list)
	{
		if (!(tmp = ft_strmjoin(path, "/", list->content)))
			return (NULL);
		if (!(ls_lb(tab, tmp)))
			return (NULL);
		list = list->next;
	}
	return (tab);
}

int		*ls_lb(int *tab, char *path)
{
	struct stat infos;

	if (lstat(path, &infos) != 0)
	{
		ft_strdel(&path);
		ft_memdel((void *)&tab);
		return (NULL);
	}
	if (!(tab = ls_blanks(infos, tab)))
	{
		ft_strdel(&path);
		ft_memdel((void *)&tab);
		return (NULL);
	}
	tab[0] = tab[0] + infos.st_blocks;
	ft_strdel(&path);
	return (tab);
}

int		*ls_blanks(struct stat infos, int *tab)
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
	ft_strdbldel(&uid_name, &gid_name);
	return (tab);
}

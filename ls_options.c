/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 12:49:43 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/10 13:43:18 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_options(t_infos *infos)
{
	t_list		*list;
	t_list		*head;

	list = NULL;
	ls_begin(infos);
	head = infos->path_lst;
	while (infos->path_lst)
	{
		if (infos->opt_flags & FLG_BR)
		{
			list = ls_exec(list, infos->path_lst->content, infos->opt_flags);
			if (list)
				ft_putbn();
			ls_recursive(list, infos->path_lst->content, infos->opt_flags);
		}
		else
			list = ls_exec(list, infos->path_lst->content, infos->opt_flags);
		if (infos->path_lst->next && list)
			ft_putbn();
		if (!(infos->opt_flags & FLG_BR))
			ls_lstfree(list);
		infos->path_lst = infos->path_lst->next;
	}
	ls_lstfree(head);
}

void		ls_begin(t_infos *infos)
{
	ls_merge_sort(&infos->path_lst, &ft_strcmp);
	if (infos->opt_flags & FLG_T)
		infos->path_lst = ls_time_sort(infos->path_lst, ".");
	if (infos->opt_flags & FLG_R)
		infos->path_lst = ft_lstrev(infos->path_lst, NULL);
	if (infos->path_lst->next)
		infos->opt_flags |= M_ARG;
	ls_merge_sort(&infos->path_lst, &ls_arg_sort);
}

t_list		*ls_exec(t_list *list, char *path, int flags)
{
	struct stat	infos;
	int			i;

	i = 0;
	if (path[0] == '/' && path[1] == '/')
		i = 1;
	lstat(path, &infos);
	if (ls_error(errno, path) == 0)
	{
		if ((flags & M_ARG) && (infos.st_mode & S_IFDIR))
			ft_mprintf("ss\n", path + i, ":", NULL);
		if (!(list = ls_exec_n(list, path, flags, infos)))
			return (NULL);
		if (flags & FLG_L && (infos.st_mode & S_IFLNK))
		{
			ls_dir_link(path);
			ls_lstfree(list);
			return (NULL);
		}
		else if (flags & FLG_L && !(infos.st_mode & S_IFLNK))
			ls_list(list, path);
		else if (list)
			ft_putlst(list);
	}
	return (list);
}

t_list		*ls_exec_n(t_list *list, char *path, int flags, struct stat infos)
{
	if (!(infos.st_mode & S_IFDIR) && !(infos.st_mode & S_IFLNK))
		ft_putendl(path);
	if (!(list = ls_path_content(path, flags)))
	{
		ls_lstfree(list);
		return (NULL);
	}
	if (flags & FLG_T && !(infos.st_mode & S_IFLNK))
		list = ls_time_sort(list, path);
	if (flags & FLG_R && !(infos.st_mode & S_IFLNK))
		list = ft_lstrev(list, NULL);
	return (list);
}

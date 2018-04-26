/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 12:49:43 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/26 14:56:06 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_options(t_infos *infos)
{
	t_list		*list;

	list = NULL;
	ls_merge_sort(&infos->path_lst, &ft_strcmp);
	if (infos->opt_flags & FLG_R)
		infos->path_lst = ft_lstrev(infos->path_lst, NULL);
	if (infos->path_lst->next)
		infos->opt_flags |= M_ARG;
	ls_merge_sort(&infos->path_lst, &ls_arg_sort);
	while (infos->path_lst)
	{
		if (infos->opt_flags & FLG_BR)
		{
			list = ls_execution(list, infos->path_lst->content, infos->opt_flags);
			if (list)
				ft_putbn();
			ls_recursive(list, infos->path_lst->content, infos->opt_flags);
		}
		else
			list = ls_execution(list, infos->path_lst->content, infos->opt_flags);
		if (infos->path_lst->next && list)
			ft_putbn();
		infos->path_lst = infos->path_lst->next;
	}
}

int			ls_arg_sort(char *arg1, char *arg2)
{
	struct stat			infos1;
	struct stat			infos2;
	int					stat_return[2];

	stat_return[0] = lstat(arg1, &infos1);
	stat_return[1] = lstat(arg2, &infos2);
	if (((infos1.st_mode & S_IFDIR) && !(infos2.st_mode & S_IFDIR)) ||
				(stat_return[0] == 0 && stat_return[1] != 0))
		return (1);
	return (0);
}

t_list		*ls_execution(t_list *list, char *path, int flags)
{
	struct stat	infos;
	int			i;
	int 		error;

	i = 0;
	if (path[0] == '/')
		i = 1;
	error = lstat(path, &infos);
	ls_error(errno, path);
	if (error == 0)
	{
		if ((flags & M_ARG) && (infos.st_mode & S_IFDIR))
			ft_putmthings(path + i, ":", NULL, 0);
		if (!(infos.st_mode & S_IFDIR))
			ft_putendl(path);
		list = ls_path_content(path, flags);
		if (flags & FLG_T)
			list = ls_time_sort(list, path);
		if (flags & FLG_R)
			list = ft_lstrev(list, NULL);
		if (flags & FLG_L)
			ls_list(list, path);
		else if (list)
			ft_putlst(list);
	}
	return (list);
}

t_list		*ls_path_content(char *path, int flags)
{
	DIR					*dir;
	struct dirent		*directory;
	t_list				*tmp;
	t_list				*content_list;

	tmp = NULL;
	content_list = NULL;
	if (!(dir = opendir(path)))
	{
		ls_error(errno, path);
		return (NULL);
	}
	while ((directory = readdir(dir)) != NULL)
	{
		if (!(flags & FLG_A))
			while (directory->d_name[0] == '.')
				if ((directory = readdir(dir)) == NULL)
					return (NULL);
		if (!(tmp = ft_lstnew(directory->d_name, sizeof(directory->d_name))))
			return (NULL);
		ft_lstadd(&content_list, tmp);
	}
	if (closedir(dir) == -1)
		return (NULL);
	ls_merge_sort(&content_list, &ft_strcmp);
	return (content_list);
}

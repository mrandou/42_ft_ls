/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 12:49:43 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/09 17:46:09 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_options(t_infos *infos)
{
	t_list		*list;
	t_list		*head;

	list = NULL;
	ls_merge_sort(&infos->path_lst, &ft_strcmp);
	if (infos->opt_flags & FLG_T)
		infos->path_lst = ls_time_sort(infos->path_lst, ".");
	if (infos->opt_flags & FLG_R)
		infos->path_lst = ft_lstrev(infos->path_lst, NULL);
	if (infos->path_lst->next)
		infos->opt_flags |= M_ARG;
	ls_merge_sort(&infos->path_lst, &ls_arg_sort);
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

t_list		*ls_path_content(char *path, int flags)
{
	DIR					*dir;
	struct dirent		*directory;
	t_list				*tmp;
	t_list				*content_list;

	tmp = NULL;
	content_list = NULL;
	if (ls_access(path) == -1)
		return (NULL);
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
				{
					if (closedir(dir) == -1)
						return (NULL);
					return (NULL);
				}
		if (!(tmp = ft_lstnew(directory->d_name, sizeof(directory->d_name))))
			return (NULL);
		ft_lstadd(&content_list, tmp);
	}
	if (closedir(dir) == -1)
		return (NULL);
	ls_merge_sort(&content_list, &ft_strcmp);
	return (content_list);
}

int			ls_access(char *path)
{
	struct stat 	infos;

	lstat(path, &infos);
	if (ls_error(errno, path) == -1)
		return (-1);
	if (infos.st_mode & S_IXUSR)
		return (1);
	return (0);
}
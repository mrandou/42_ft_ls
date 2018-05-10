/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:28:02 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/10 13:42:42 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*ls_path_content(char *path, int flags)
{
	DIR		*dir;
	t_list	*list;

	list = NULL;
	if (ls_access(path) == -1)
		return (NULL);
	if (!(dir = opendir(path)))
	{
		ls_error(errno, path);
		return (NULL);
	}
	if (!(list = ls_read(flags, dir)))
		return (NULL);
	ls_merge_sort(&list, &ft_strcmp);
	return (list);
}

t_list		*ls_read(int flags, DIR *dir)
{
	struct dirent	*directory;
	t_list			*tmp;
	t_list			*content_list;

	tmp = NULL;
	content_list = NULL;
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
	return (content_list);
}

int			ls_access(char *path)
{
	struct stat	infos;

	lstat(path, &infos);
	if (ls_error(errno, path) == -1)
		return (-1);
	if (infos.st_mode & S_IXUSR)
		return (1);
	return (0);
}

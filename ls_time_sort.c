/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_time_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:30:39 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/03 18:18:27 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char *get_path(char *path)
{
	static char *cpy_path;

	if (path)
	{
		if (!(path = ft_strjoin(path, "/")))
			return (NULL);
		if (!(cpy_path = ft_strdup(path)))
			return (NULL);
		ft_strdel(&path);
	}
	return (cpy_path);
}

int     date_cmp(char *date1, char *date2)
{
	struct stat infos1;
	struct stat infos2;
	char *path;

	if (!(path = get_path(NULL)))
		return (0);
	if (!(date1 = ft_strjoin(path, date1)))
			return (-1);
	if (!(date2 = ft_strjoin(path, date2)))
		return (-1);
	lstat(date1, &infos1);
	if (ls_error(errno, date1) == -1)
		return (0);
	lstat(date2, &infos2);
	if (ls_error(errno, date2) == -1)
		return (0);
	ft_strdel(&date1);
	ft_strdel(&date2);
	if (infos1.st_mtime < infos2.st_mtime)
	 return (1);
	return (0);
}

t_list 	*ls_time_sort(t_list *list, char *path)
{
	if (!(get_path(path)))
		return (NULL);
	ls_merge_sort(&list, &date_cmp);
	if (!list)
		return (NULL);
	return (list);
}

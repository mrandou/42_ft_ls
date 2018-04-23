/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_time_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:30:39 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/23 18:02:27 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char *get_path(char *path)
{
  static char *cpy_path;

  if (!cpy_path)
  {
    path = ft_strjoin(path, "/");
    cpy_path = ft_strdup(path);
  }
  return (cpy_path);
}

int     date_cmp(t_list *d1, t_list *d2)
{
    struct stat infos1;
    struct stat infos2;
    char *path_date1;
    char *path_date2;
    char *path;

    path = get_path(NULL);
    path_date1 = ft_strjoin(path, (char *)d1);
    path_date2 = ft_strjoin(path, (char *)d2);
    lstat(path_date1, &infos1);
		ls_error(errno, path_date1);
    lstat(path_date2, &infos2);
		ls_error(errno, path_date2);
    ft_strdel(&path_date1);
    ft_strdel(&path_date2);
    if (infos1.st_mtime > infos2.st_mtime)
      return (1);
    return (0);
}

t_list 	*ls_time_sort(t_list *list, char *path)
{
  get_path(path);
  ls_merge_sort(&list, &date_cmp);
	if (!list)
		return (NULL);
	return (list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:55:45 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/07 15:16:35 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_recursive(t_list *list, char *path, int flags)
{
	flags |= M_ARG;
	while (list)
	{
		if (!(list = ls_skip_points(list)))
			return ;
		ls_recursive_exec(path, list->content, flags);
		if (!list->next)
			return ;
		list = list->next;
	}
	ls_lstfree(list);
}

t_list		*ls_skip_points(t_list *list)
{
	if (!ft_strcmp(list->content, "."))
	{
		if (list->next)
			list = list->next;
		else
			return (NULL);
	}
	if (!ft_strcmp(list->content, ".."))
	{
		if (list->next)
			list = list->next;
		else
			return (NULL);
	}
	if (!ft_strcmp(list->content, "."))
	{
		if (list->next)
			list = list->next;
		else
			return (NULL);
	}
	return (list);
}

void		ls_recursive_exec(char *path, char *scpath, int flags)
{
	struct stat	infos;
	char *tmp;
	t_list *nxtlst;

	nxtlst = NULL;
	tmp = NULL;
	if (!scpath || !path)
		return ;
	if (!(tmp = ft_strjoin(path, "/")))
		return ;
	if (!(tmp = ft_strjoin(tmp, scpath)))
		return ;
	if (lstat(tmp, &infos) != 0)
		return ;
	if (infos.st_mode & S_IFDIR)
	{
		nxtlst = ls_exec(nxtlst, tmp, flags);
		ft_putbn();
		ls_recursive(nxtlst, tmp, flags);
		ft_strdel(&tmp);
	}
	ft_strdel(&scpath);
}

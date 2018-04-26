/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:55:45 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/26 13:35:02 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_recursive(t_list *list, char *path, int flags)
{

	flags |= M_ARG;
	while (list)
	{
		if (!ft_strcmp(list->content, "."))
			list = list->next;
		if (!ft_strcmp(list->content, ".."))
		{
			if (list->next)
				list = list->next;
			else
				return ;
		}
		ls_recursive_exec(path, list->content, flags);
		list = list->next;
	}
  ft_lstdel(&list, (void *)&ft_strdel);
}

void		ls_recursive_exec(char *path, char *scpath, int flags)
{
	struct stat	infos;
	char *tmp;
	t_list *nxtlst;

	nxtlst = NULL;
	tmp = NULL;
	if (!(tmp = ft_strjoin(path, "/")))
		return ;
	if (!(tmp = ft_strjoin(tmp, scpath)))
		return ;
	lstat(tmp, &infos);
	if (infos.st_mode & S_IFDIR)
	{
		nxtlst = ls_execution(nxtlst, tmp, flags);
		ft_putbn(); //ne pas le mettre a la derniere ligne
		ls_recursive(nxtlst, tmp, flags);
		ft_strdel(&tmp);
	}
	ft_strdel(&scpath);
}

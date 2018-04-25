/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 13:55:45 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/25 18:05:50 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_recursive(t_list *list, char *path, int flags)
{
	t_list *nxtlst;

	nxtlst = NULL;
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
		ls_recursive_exec(nxtlst, path, list->content, flags);
		list = list->next;
	}
  ft_lstdel(&list, (void *)&ft_strdel);
}

void		ls_recursive_exec(t_list *nxtlst, char *path, char *scpath, int flags)
{
	struct stat	infos;
	char *tmp;

	tmp = NULL;
	if (!(tmp = ft_strjoin(path, "/")))
		return ;
	if (!(tmp = ft_strjoin(tmp, scpath)))
		return ;
	lstat(tmp, &infos);
	if (infos.st_mode & S_IFDIR)
	{
		nxtlst = ls_path_content(tmp, flags);
		ls_print(nxtlst, tmp, flags);
		ft_putbn();
		ls_recursive(nxtlst, tmp, flags);
		ft_strdel(&tmp);
	}
	ft_strdel(&scpath);
}

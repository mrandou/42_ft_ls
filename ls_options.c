/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 12:49:43 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/23 18:06:19 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void 	ls_options(t_infos *infos)
{
	t_list *content_list;

	content_list = NULL;
	ls_merge_sort(&infos->path_lst, &ft_strcmp);
	if (infos->opt_flags & FLG_R)
		infos->path_lst = ft_lstrev(infos->path_lst, NULL);
	if (infos->path_lst->next)
		infos->opt_flags |= M_ARG;
	while (infos->path_lst)
	{
		content_list = ls_path_content(infos->path_lst->content, infos->opt_flags);
		ls_print(content_list, infos->path_lst->content, infos->opt_flags);
		if (infos->path_lst->next)
			ft_putbn();
		infos->path_lst = infos->path_lst->next;
	}
}

void 		ls_print(t_list *list, char *path, int flags)
{
	if (flags & M_ARG)
		ft_putmthings(path, ":", NULL, 0);
	if (flags & FLG_T)
		list = ls_time_sort(list, path);
	if (!(flags & FLG_R))
		list = ft_lstrev(list, NULL);
	ft_putlst(list);
}

t_list	*ls_path_content(char *path, int flags)
{
	DIR 					*dir;
	struct dirent	*directory;
	t_list 				*tmp;
	t_list				*content_list;

	tmp = NULL;
	content_list = NULL;
	if (!(dir = opendir(path)))
		return (NULL);
	while ((directory = readdir(dir)) != NULL)
	{
		if (!(flags & FLG_A))
		{
			while (directory->d_name[0] == '.')
				if ((directory = readdir(dir)) == NULL)
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

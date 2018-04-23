/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:23:32 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/23 17:28:54 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ls_parse(char **argv, int argc, t_infos *infos)
{
	t_list	*tmp;
	int nb_flags;

	nb_flags = 0;
	tmp = NULL;
	while (*argv)
	{
		if (**argv == '-')
		{
			infos->opt_flags |= ls_get_flags(*argv);
			nb_flags++;
		}
		else
		{
			if (!(tmp = ft_lstnew(*argv, sizeof(*argv))))
				return (-1);
			ft_lstadd(&infos->path_lst, tmp);
		}
		argv++;
	}
	if (nb_flags == (argc - 1))
		if (!(infos->path_lst = ft_lstnew(".", sizeof(char *))))
			return (-1);
	return (0);
}

unsigned	int	ls_get_flags(char *arg)
{
	unsigned int flag;

	flag = 0;
	while (*arg)
	{
		if (*arg == 'l')
			flag |= FLG_L;
		if (*arg == 'R')
			flag |= FLG_BR;
		if (*arg == 'a')
			flag |= FLG_A;
		if (*arg == 'r')
			flag |= FLG_R;
		if (*arg == 't')
			flag |= FLG_T;
		arg++;
	}
	return (flag);
}

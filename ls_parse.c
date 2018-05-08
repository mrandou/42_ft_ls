/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:23:32 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/08 14:00:51 by mrandou          ###   ########.fr       */
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
		if (**argv == '-' && !tmp)
		{
			infos->opt_flags |= ls_get_flags(*argv);
			nb_flags++;
		}
		else
		{
			if (!(tmp = ft_lstnew(*argv, ft_strlen(*argv) + 1)))
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
	if (ft_countoc(arg, '-') > 2)
			ls_error(BAD_FLAG, &*arg);
	if (ft_countoc(arg, '-') == 1 && !arg[1])
	{
			flag |= M_ARG;
			ls_error(BAD_ARG, "-");
			return (0);
	}
	arg++;
	while (*arg)
	{
		if (!(ft_strchr("-lRart", *arg)))
			ls_error(BAD_FLAG, &*arg);
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
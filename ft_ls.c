/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:19:31 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/20 18:09:08 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	t_infos	infos;

	infos.opt_flags = 0;
	infos.path_lst = NULL;
	if (ls_parse(argc, argv, &infos) != 0)
		return (-1);
}

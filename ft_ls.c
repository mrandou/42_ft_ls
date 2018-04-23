/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:19:31 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/23 17:55:36 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ls_error(int code, char *path)
{
	if (code == ENOENT)
  {
    ft_putstr("./ft_ls: ");
    perror(path);
  }
}

int main(int argc, char **argv)
{
	t_infos	infos;

	infos.opt_flags = 0;
	infos.path_lst = NULL;
	if (ls_parse(++argv, argc, &infos) != 0)
		return (-1);
	ls_options(&infos);
	return (argc);
}

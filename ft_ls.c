/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:19:31 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/03 18:23:16 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int ls_error(int code, char *name)
{
	if (code == BAD_FLAG)
	{
		ft_mprintf("ss2\n", "./ft_ls: illegal option -- ",
		ft_strcut(name, 0, 1), NULL);
		ft_putendl_fd("usage: ft_ls: [-lRart] [file...]", 2);
		exit(0);
	}
	if (code == BAD_ARG)
		ft_mprintf("sss2\n", "./ft_ls: ", name, ": No such file or directory");
	if (code == ENOENT)
	{
		ft_putstr("./ft_ls: ");
		perror(name);
	}
	if (code == EACCES)
	{
		ft_putstr_fd("./ft_ls: ", 2);
		name = ft_strrchr(name, '/');
		if (name[0] == '/')
			perror(&name[1]);
		else
			perror(name);
	}
	errno = 0;
	if (code)
		return (-1);
	return (0);
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

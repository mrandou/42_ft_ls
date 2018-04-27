/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:19:31 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/27 18:42:53 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ls_error(int code, char *name)
{
	if (code == BAD_FLAG)
	{
    ft_putstr("./ft_ls: illegal option -- ");
    ft_putchar(name[0]);
    ft_putbn();
    ft_putendl("usage: ft_ls: [-lRart] [file...]");
    exit(0);
	}
	if (code == BAD_ARG)
    ft_putmthings("./ft_ls: ", name, ": No such file or directory", 0);
	if (code == ENOENT)
  {
    ft_putstr("./ft_ls: ");
    perror(name);
  }
	if (errno == EACCES)
  {
    ft_putstr("./ft_ls: ");
    name = ft_strrchr(name, '/');
    if (name[0] == '/')
      perror(&name[1]);
    else
      perror(name);
  }
	errno = 0;
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

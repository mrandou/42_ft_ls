/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:20:08 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/23 18:00:37 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

# define	FLG_L		0b000001
# define	FLG_BR	0b000010
# define	FLG_A		0b000100
# define	FLG_R 	0b001000
# define	FLG_T		0b010000
# define	M_ARG		0b100000

typedef struct s_infos
{
	unsigned int		opt_flags;
	t_list 					*path_lst;
}								t_infos;

void 					ls_error(int code, char *path);

int 					ls_parse(char **argv, int argc, t_infos *infos);
unsigned int	ls_get_flags(char *arg);

void 					ls_options(t_infos *infos);
void 					ls_print(t_list *list, char *path, int flags);
t_list				*ls_path_content(char *path, int flags);

void 					ls_merge_sort(t_list **list, int (*f_cmp)());

t_list 				*ls_time_sort(t_list *list, char *path);

#endif

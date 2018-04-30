/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:20:08 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/30 17:10:55 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include"libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

# define	FLG_L			0b000001
# define	FLG_BR			0b000010
# define	FLG_A			0b000100
# define	FLG_R 			0b001000
# define	FLG_T			0b010000
# define	M_ARG			0b100000

# define	SIX_MONTH		15770000

# define	BAD_FLAG		404
# define	BAD_ARG			604

typedef struct 			s_infos
{
	unsigned int		opt_flags;
	t_list 				*path_lst;
}						t_infos;

int						ls_error(int code, char *path);

int						ls_parse(char **argv, int argc, t_infos *infos);
unsigned int			ls_get_flags(char *arg);

void					ls_options(t_infos *infos);
int						ls_arg_sort(char *arg1, char *arg2);
t_list					*ls_execution(t_list *list, char *path, int flags);
t_list					*ls_path_content(char *path, int flags);

void 					ls_merge_sort(t_list **list, int (*f_cmp)());

t_list 					*ls_time_sort(t_list *list, char *path);

void					ls_recursive(t_list *list, char *path, int flags);
void					ls_recursive_exec(char *path, char *sc, int f);

void					ls_list(t_list *list, char *path);
void					ls_print_infos(struct stat infos, char *name, int *tab);
int						*ls_links_and_blanks(t_list *list, char *path);
int						*ls_blanks(struct stat infos, int *tab);

char					*ls_permission(struct stat infos);
char					ls_get_type(struct stat infos);
int						ls_access(char *path);

#endif

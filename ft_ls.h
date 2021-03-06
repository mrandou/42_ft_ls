/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:20:08 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/11 11:00:47 by mrandou          ###   ########.fr       */
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

# define FLG_L			0b000001
# define FLG_BR			0b000010
# define FLG_A			0b000100
# define FLG_R 			0b001000
# define FLG_T			0b010000
# define M_ARG			0b100000

# define SIX_MONTH		15770000
# define BAD_FLAG		404

typedef struct		s_infos
{
	unsigned int	opt_flags;
	t_list			*path_lst;
}					t_infos;

int					ls_error(int code, char *path);
void				ls_lstfree(t_list *list);

int					ls_parse(char **argv, int argc, t_infos *infos);
unsigned int		ls_get_flags(char *arg);
int					ls_arg_sort(char *arg1, char *arg2);

void				ls_options(t_infos *infos);
void				ls_begin(t_infos *infos);
t_list				*ls_exec(t_list *list, char *path, int flags);
t_list				*ls_exec_n(t_list *lst, char *pth, int flg, struct stat in);

t_list				*ls_path_content(char *path, int flags);
t_list				*ls_read(int flags, DIR *dir);
int					ls_access(char *path);

void				ls_merge_sort(t_list **list, int (*f_cmp)());

t_list				*ls_time_sort(t_list *list, char *path);

void				ls_recursive(t_list *list, char *path, int flags);
void				ls_recursive_exec(char *path, char *sc, int f);
t_list				*ls_skip_points(t_list *list);

void				ls_list(t_list *list, char *path);
int					*ls_links_and_blanks(t_list *list, char *path);
int					*ls_lb(int *tab, char *path);
int					*ls_blanks(struct stat infos, int *tab);

char				*ls_permission(struct stat infos);
char				*ls_sticky_and_sgid(struct stat infos, char *permisssion);
char				ls_get_type(struct stat infos);
char				*ls_get_user(struct stat infos);
char				*ls_get_group(struct stat infos);

void				ls_print_infos(struct stat in, char *pa, char *n, int *tab);
void				ls_symb_link(char *path, struct stat infos);
void				ls_dir_link(char *path);
void				ls_get_date(struct stat infos);
void				ls_size_major_minor(struct stat infos, int *tab);

#endif

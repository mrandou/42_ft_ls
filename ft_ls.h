/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:20:08 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/20 17:49:00 by mrandou          ###   ########.fr       */
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

# define	FLG_L		0b00001
# define	FLG_BR	0b00010
# define	FLG_A		0b00100
# define	FLG_R 	0b01000
# define	FLG_T		0b10000

typedef struct s_infos
{
	unsigned int		 opt_flags;
	t_list *path_lst;
}								t_infos;

#endif

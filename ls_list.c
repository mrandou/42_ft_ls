/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:52:38 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/30 17:14:17 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_list(t_list *list, char *path_name) //pointeur sur fonction ? stat <-> lstat
{
	struct stat	infos;
	char		*path;
	int			*tab;

	path = NULL;
	tab = ls_links_and_blanks(list, path_name);
	if (list)
		ft_putmthings("total ", NULL, NULL, tab[0]);
	while (list)
	{
		if (!(path = ft_strjoin(path_name, "/")))
			return ;
		if (!(path = ft_strjoin(path, list->content)))
			return ;
		lstat(path, &infos);
		if (ls_error(errno, path) == -1)
			return ;
		if (errno)
			list = list->next;
		ls_print_infos(infos, list->content, tab);
		ft_strdel(&path);
		list = list->next;
	}
	ft_lstdel(&list, (void *)&ft_strdel);
	ft_memdel((void *)&tab);
}

void		ls_print_infos(struct stat infos, char *name, int *tab)
{
	struct passwd	*user;
	struct group	*grp;
	char			*permi;

	user = getpwuid(infos.st_uid); //			RECUP ERREUR UID;
	grp = getgrgid(infos.st_gid);
	permi = ls_permission(infos);
	ft_putstr(permi);
	ft_putnchar(' ', tab[1] - ft_nblen(infos.st_nlink) + 2);
	ft_putnbr(infos.st_nlink);
	ft_mprintf("ss", " ", user->pw_name, NULL);
	ft_putnchar(' ', tab[2] - ft_strlen(user->pw_name));
	ft_putstr(grp->gr_name);
	ft_putnchar(' ', tab[3] - ft_strlen(grp->gr_name));
	ft_putnchar(' ', tab[4] - ft_nblen(infos.st_size));
	ft_mprintf("ds", (void *)infos.st_size, " ", NULL);
	if ((time(NULL) - infos.st_mtime) > SIX_MONTH)
		ft_mprintf("sss", ft_strcut(ctime(&infos.st_mtime), 4, 11), " ",
		ft_strcut(ctime(&infos.st_mtime), 20, 24));
	else
		ft_putstr(ft_strcut(ctime(&infos.st_mtime), 4, 16));
	ft_mprintf("ss\n", " ", name, NULL);
	ft_strdel(&permi);
}
//./ft_ls -lR /private/etc

int		*ls_links_and_blanks(t_list *list, char *path)
{
	struct	stat 			infos;
	char					*tmp;
	int						*tab;
	int						i;

	if (!(tab = ft_memalloc(17)))
		return (NULL);
	i = 0;
	while (i < 5)
		tab[i++] = 0;
	while (list)
	{
		if (!(tmp = ft_strjoin(path, "/")))
			return (0);
	  if (!(tmp = ft_strjoin(tmp, list->content)))
			return (0);
		if (lstat(tmp, &infos) != 0)
			return (0);
		if (!(tab = ls_blanks(infos, tab)))
			return (NULL);
		tab[0] = tab[0] + infos.st_blocks;
		ft_strdel(&tmp);
		list = list->next;
	}
	return (tab);
}

int			*ls_blanks(struct stat infos, int *tab)
{
	struct passwd	*user;
	struct group	*grp;

	user = getpwuid(infos.st_uid);
	grp = getgrgid(infos.st_gid);
	if (tab[1] < ft_nblen(infos.st_nlink))
		tab[1] = ft_nblen(infos.st_nlink);
	if (tab[2] < ((int)ft_strlen(user->pw_name) + 2))
		tab[2] = ((int)ft_strlen(user->pw_name) + 2);
	if (tab[3] < ((int)ft_strlen(grp->gr_name)))
		tab[3] = ((int)ft_strlen(grp->gr_name));
	if (tab[4] < ft_nblen(infos.st_size) + 2)
		tab[4] = ft_nblen(infos.st_size) + 2;
	return (tab);
}

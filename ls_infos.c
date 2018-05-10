/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_infos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:21:53 by mrandou           #+#    #+#             */
/*   Updated: 2018/05/10 14:48:52 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ls_permission(struct stat infos)
{
	char	*permission;

	if (!(permission = ft_strdup("----------")))
		return (NULL);
	if (infos.st_mode & S_IRUSR)
		permission[1] = 'r';
	if (infos.st_mode & S_IWUSR)
		permission[2] = 'w';
	if (infos.st_mode & S_IXUSR)
		permission[3] = 'x';
	if (infos.st_mode & S_IRGRP)
		permission[4] = 'r';
	if (infos.st_mode & S_IWGRP)
		permission[5] = 'w';
	if (infos.st_mode & S_IXGRP)
		permission[6] = 'x';
	if (infos.st_mode & S_IROTH)
		permission[7] = 'r';
	if (infos.st_mode & S_IWOTH)
		permission[8] = 'w';
	if (infos.st_mode & S_IXOTH)
		permission[9] = 'x';
	permission[0] = ls_get_type(infos);
	permission = ls_sticky_and_sgid(infos, permission);
	return (permission);
}

char		*ls_sticky_and_sgid(struct stat infos, char *permission)
{
	if (infos.st_mode & S_ISUID)
		permission[3] = 'S';
	if (infos.st_mode & S_ISGID)
		permission[6] = 'S';
	if (infos.st_mode & S_ISVTX)
		permission[9] = 'T';
	if ((infos.st_mode & S_ISUID) && (infos.st_mode & S_IXUSR))
		permission[3] = 's';
	if ((infos.st_mode & S_ISGID) && (infos.st_mode & S_IXGRP))
		permission[6] = 's';
	if (infos.st_mode & S_ISVTX && (infos.st_mode & S_IXOTH))
		permission[9] = 't';
	return (permission);
}

char		ls_get_type(struct stat infos)
{
	char	type;

	type = '?';
	if ((infos.st_mode & S_IFMT) == S_IFLNK)
		type = 'l';
	if ((infos.st_mode & S_IFMT) == S_IFREG)
		type = '-';
	if ((infos.st_mode & S_IFMT) == S_IFSOCK)
		type = 's';
	if ((infos.st_mode & S_IFMT) == S_IFIFO)
		type = 'p';
	if ((infos.st_mode & S_IFMT) == S_IFDIR)
		type = 'd';
	if ((infos.st_mode & S_IFMT) == S_IFCHR)
		type = 'c';
	if ((infos.st_mode & S_IFMT) == S_IFBLK)
		type = 'b';
	return (type);
}

char		*ls_get_user(struct stat infos)
{
	struct passwd	*user;
	char			*uid_name;

	uid_name = NULL;
	if (!(user = getpwuid(infos.st_uid)))
	{
		if (!(uid_name = ft_itoa(infos.st_uid)))
			return (NULL);
	}
	else
	{
		if (!(uid_name = ft_strdup(user->pw_name)))
			return (NULL);
	}
	return (uid_name);
}

char		*ls_get_group(struct stat infos)
{
	struct group	*grp;
	char			*gid_name;

	gid_name = NULL;
	if (!(grp = getgrgid(infos.st_gid)))
	{
		if (!(gid_name = ft_itoa(infos.st_gid)))
			return (NULL);
	}
	else
	{
		if (!(gid_name = ft_strdup(grp->gr_name)))
			return (NULL);
	}
	return (gid_name);
}

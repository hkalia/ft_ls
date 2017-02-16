/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 14:35:19 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/15 20:50:07 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern uint8_t	g_ft_ls_flgs;
extern int8_t	ret;

static void		lhandler_dir(t_arr *files)
{
	t_ft_ls_file	*tmp;
	int				widths[4];
	long long		blks;
	size_t			i;

	tmp = (t_ft_ls_file *)files->ptr;
	ft_bzero(widths, 4 * sizeof(int));
	blks = 0;
	i = 0;
	while (i < files->len)
	{
		ft_ls_get_widths(widths, tmp[i].info);
		blks += tmp[i++].info.st_blocks;
	}
	printf("total %lld\n", blks);
	i = 0;
	while (i < files->len)
		ft_ls_print_l(widths, tmp[i++]);
}

int8_t	ft_ls_get_dir(t_arr *files, char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_ft_ls_file	tmp;

	GRD((dirp = opendir(path)) == 0, -1);
	GRD(arr_init(files, 10, (t_arr_elm){sizeof(t_ft_ls_file), 0, file_dup
		, file_dtr}) == -1, -1);
	while ((dp = readdir(dirp)) != 0)
	{
		if (dp->d_name[0] == '.' && !(g_ft_ls_flgs & 0x4))
			continue ;
		ft_asprintf(&tmp.path, "%s/%s", path, dp->d_name);
		tmp.basename = dp->d_name;
		GRD3(lstat(tmp.path, &tmp.info) == -1, free(tmp.path), arr_dtr(files)
			, closedir(dirp), -1);
		GRD3(arr_append(files, &tmp) == -1, free(tmp.path), arr_dtr(files)
			, closedir(dirp), -1);
		free(tmp.path);
	}
	closedir(dirp);
	return (0);
}

int8_t			ft_ls_print_dir(char *path)
{
	t_arr			files;
	t_ft_ls_file	*tmp;
	size_t			i;

	GRD1(ft_ls_get_dir(&files, path) == -1, ft_dprintf(STDERR_FILENO
		, "ls: %s: %s\n", ft_ls_basename(path), strerror(errno)), -1);
	GRD1(files.len == 0, arr_dtr(&files), -1);
	tmp = (t_ft_ls_file *)files.ptr;
	i = 0;
	ft_ls_sort(&files);
	if (g_ft_ls_flgs & 0x1)
		lhandler_dir(&files);
	else
		while (i < files.len)
			printf("%s\n", tmp[i++].basename);
	if (g_ft_ls_flgs & 0x2)
	{
		i = 0;
		while (i < files.len)
		{
			if (S_ISDIR(tmp[i].info.st_mode)
				&& !(ft_strcmp(tmp[i].basename, ".") == 0
				|| ft_strcmp(tmp[i].basename, "..") == 0))
			{
				printf("\n%s:\n", tmp[i].path);
				ft_ls_print_dir(tmp[i].path);
			}
			++i;
		}
	}
	arr_dtr(&files);
	return (0);
}

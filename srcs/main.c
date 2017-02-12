/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 15:28:07 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/11 17:12:59 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint8_t			g_ft_ls_flgs = 0;
int8_t			ret = 0;

// static int8_t	parser(int argc, char **argv)
// {
// 	int		i;
// 	size_t	j;
//
// 	i = 1;
// 	while (i < argc && argv[i][0] == '-')
// 	{
// 		if (argv[i][1] == '-')
// 			break ;
// 		j = 0;
// 		while (argv[i][++j] != 0)
// 		{
// 			if (argv[i][j] == 'l')
// 				g_ft_ls_flgs |= 0x1;
// 			else if (argv[i][j] == 'R')
// 				g_ft_ls_flgs |= 0x2;
// 			else if (argv[i][j] == 'a')
// 				g_ft_ls_flgs |= 0x4;
// 			else if (argv[i][j] == 'r')
// 				g_ft_ls_flgs |= 0x8;
// 			else if (argv[i][j] == 't')
// 				g_ft_ls_flgs |= 0x10;
// 			else if (argv[i][j] == '1');
// 			else
// 				return (-1);
// 		}
// 		++i;
// 	}
// 	if (i < argc)
// 		GRD(ft_ls_handle_args(i, argc, argv) == -1, -1);
// 	else
// 		GRD(ft_ls_print_dir(".") == -1, -1);
// 	return (ret);
// }
//
// int		main(int argc, char **argv)
// {
// 	if (argc == 1)
// 		GRD(ft_ls_print_dir(".") == -1, -1);
// 	else if (argc > 1)
// 		GRD(parser(argc, argv) == -1, -1);
// 	else
// 		return(-1);
// 	return (ret);
// }

int8_t	file_dup(void *dst, const void *src)
{
	t_ft_ls_file	*dst_cpy;
	t_ft_ls_file	*src_cpy;

	dst_cpy = (t_ft_ls_file *)dst;
	src_cpy = (t_ft_ls_file *)src;
	GRD((dst_cpy->path = ft_strdup(src_cpy->path)) == 0, -1);
	GRD1((dst_cpy->basename = ft_strdup(src_cpy->basename)) == 0
		, free(dst_cpy->path), -1);
	dst_cpy->info = src_cpy->info;
	return (0);
}

void	file_dtr(void *elm)
{
	free(((t_ft_ls_file *)elm)->basename);
	free(((t_ft_ls_file *)elm)->path);
	ft_bzero(elm, sizeof(t_ft_ls_file));
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
		asprintf(&tmp.path, "%s/%s", path, dp->d_name);
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

int		main(void)
{
	t_arr			files;
	t_ft_ls_file	*tmp;
	size_t			i;

	GRD(ft_ls_get_dir(&files, ".") == -1, -1);
	tmp = (t_ft_ls_file *)files.ptr;
	i = 0;
	while (i < files.len)
		printf("%s\n", tmp[i++].basename);
	arr_dtr(&files);
	return (0);
}

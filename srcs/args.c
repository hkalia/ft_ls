/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 11:35:59 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/15 21:18:15 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern uint8_t	g_ft_ls_flgs;

char			*ft_ls_basename(char *path)
{
	char	*base;

	base = path;
	while (*path)
	{
		if (*path++ == '/')
			base = path;
	}
	return (base);
}

static int8_t	handle_dirs(t_arr *dirs)
{
	t_ft_ls_file	*tmp;
	size_t			i;

	tmp = (t_ft_ls_file *)dirs->ptr;
	i = 0;
	if (dirs->len == 1)
		return (ft_ls_print_dir(tmp[i].path) == -1 ? -1 : 0);
	while (i < dirs->len)
	{
		ft_printf("\n%s:\n", tmp[i].basename);
		GRD(ft_ls_print_dir(tmp[i].path) == -1, -1);
		++i;
	}
	return (0);
}

static void		handle_files(t_arr *files)
{
	t_ft_ls_file	*tmp;
	int				widths[4];
	size_t			i;

	tmp = (t_ft_ls_file *)files->ptr;
	ft_bzero(widths, 4 * sizeof(int));
	i = 0;
	if (g_ft_ls_flgs & 0x1)
	{
		while (i < files->len)
			ft_ls_get_widths(widths, tmp[i++].info);
		i = 0;
		while (i < files->len)
			ft_ls_print_l(widths, tmp[i++]);
	}
	else
		ft_printf("%s\n", tmp[i++].path);
}

int8_t			ft_ls_handle_args(int i, int argc, char **argv)
{
	t_arr			files;
	t_arr			dirs;
	t_ft_ls_file	tmp;

	GRD(arr_init(&files, (argc - i) + 2, (t_arr_elm){sizeof(t_ft_ls_file), 0
		, file_dup, file_dtr}) == -1, -1);
	GRD1(arr_init(&dirs, (argc - i) + 2, (t_arr_elm){sizeof(t_ft_ls_file), 0
		, file_dup, file_dtr}) == -1, arr_dtr(&files), -1);
	while (i < argc)
	{
		if (lstat(argv[i], &tmp.info) == -1)
		{
			ft_dprintf(STDERR_FILENO, "ls: %s: %s\n", argv[i++]
						, strerror(errno));
			continue ;
		}
		tmp.basename = ft_ls_basename(argv[i]);
		tmp.path = argv[i];
		if (S_ISDIR(tmp.info.st_mode))
			GRD2(arr_append(&dirs, &tmp) == -1, arr_dtr(&files), arr_dtr(&dirs)
				, -1);
		else
			GRD2(arr_append(&files, &tmp) == -1, arr_dtr(&files), arr_dtr(&dirs)
				, -1);
		++i;
	}
	ft_ls_sort(&files);
	handle_files(&files);
	arr_dtr(&files);
	ft_ls_sort(&dirs);
	GRD1(handle_dirs(&dirs) == -1, arr_dtr(&dirs), -1);
	arr_dtr(&dirs);
	return (0);
}

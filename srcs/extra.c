/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 14:38:54 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/15 20:47:10 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern uint8_t g_ft_ls_flgs;

int8_t		file_dup(void *dst, const void *src)
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

void		file_dtr(void *elm)
{
	if (elm == 0)
		return ;
	free(((t_ft_ls_file *)elm)->basename);
	free(((t_ft_ls_file *)elm)->path);
	ft_bzero(elm, sizeof(t_ft_ls_file));
}

static int	compare(const void *a, const void *b, size_t elm)
{
	(void)elm;
	return (ft_strcmp(((t_ft_ls_file *)a)->basename
			, ((t_ft_ls_file *)b)->basename));
}

static int	time_compare(const void *a, const void *b, size_t elm)
{
	(void)elm;
	return (((t_ft_ls_file *)b)->info.st_mtimespec.tv_sec
			- ((t_ft_ls_file *)a)->info.st_mtimespec.tv_sec);
}

void		ft_ls_sort(t_arr *files)
{
	if (g_ft_ls_flgs & 0x10)
		arr_qsort(files, time_compare);
	else
		arr_qsort(files, compare);
	if (g_ft_ls_flgs & 0x8)
		arr_reverse(files);
}

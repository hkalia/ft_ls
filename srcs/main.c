/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 15:28:07 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/15 21:19:20 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint8_t			g_ft_ls_flgs = 0;

static int8_t	parser(int argc, char **argv)
{
	int		i;
	size_t	j;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		if (argv[i][1] == '-')
			break ;
		j = 0;
		while (argv[i][++j] != 0)
		{
			if (argv[i][j] == 'l')
				g_ft_ls_flgs |= 0x1;
			else if (argv[i][j] == 'R')
				g_ft_ls_flgs |= 0x2;
			else if (argv[i][j] == 'a')
				g_ft_ls_flgs |= 0x4;
			else if (argv[i][j] == 'r')
				g_ft_ls_flgs |= 0x8;
			else if (argv[i][j] == 't')
				g_ft_ls_flgs |= 0x10;
			else if (argv[i][j] == '1')
				;
			else
				return (-1);
		}
		++i;
	}
	if (i < argc)
		GRD(ft_ls_handle_args(i, argc, argv) == -1, -1);
	else
		GRD(ft_ls_print_dir(".") == -1, -1);
	return (0);
}

int				main(int argc, char **argv)
{
	if (argc == 1)
		GRD(ft_ls_print_dir(".") == -1, -1);
	else if (argc > 1)
		GRD(parser(argc, argv) == -1, -1);
	else
		return (-1);
	return (0);
}

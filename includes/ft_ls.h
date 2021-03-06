/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 15:25:15 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/15 20:47:00 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# ifndef GRDS
#  define GRD(a, b) do{if(a){return(b);}}while(0)
#  define GRD1(a, b, c) do{if(a){b;return(c);}}while(0)
#  define GRD2(a, b, c, d) do{if(a){b;c;return(d);}}while(0)
#  define GRD3(a, b, c, d, e) do{if(a){b;c;d;return(e);}}while(0)
#  define GRD4(a, b, c, d, e, f) do{if(a){b;c;d;e;return(f);}}while(0)
#  define GRD5(a, b, c, d, e, f, g) do{if(a){b;c;d;e;f;return(g);}}while(0)
#  define GRD6(a, b, c, d, e, f, g, h) do{if(a){b;c;d;e;f;g;return(h);}}while(0)
# endif

# include <libarr.h>
# include <libft.h>
# include <libftprintf.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/syslimits.h>
# include <stdio.h>
# include <string.h>

typedef struct	s_ft_ls_file
{
	char		*path;
	char		*basename;
	struct stat	info;
}				t_ft_ls_file;

int8_t			file_dup(void *dst, const void *src);
void			file_dtr(void *elm);
int8_t			ft_ls_handle_args(int i, int argc, char **argv);
void			ft_ls_del(t_arr *files);
void			ft_ls_sort(t_arr *files);
char			*ft_ls_basename(char *path);
int8_t			ft_ls_print_dir(char *path);
void			ft_ls_get_widths(int *widths, struct stat info);
void			ft_ls_print_l(int *widths, t_ft_ls_file file);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:03:28 by hkalia            #+#    #+#             */
/*   Updated: 2017/01/28 13:31:15 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARR_H
# define ARR_H

# ifndef GRDS
#  define GRD1(a, b) do{if(a){b;}}while(0)
#  define GRD2(a, b, c) do{if(a){b;c;}}while(0)
#  define GRD3(a, b, c, d) do{if(a){b;c;d;}}while(0)
#  define GRD4(a, b, c, d, e) do{if(a){b;c;d;e;}}while(0)
#  define GRD5(a, b, c, d, e, f) do{if(a){b;c;d;e;f;}}while(0)
#  define GRD6(a, b, c, d, e, f, g) do{if(a){b;c;d;e;f;g;}}while(0)
#  define GRD7(a, b, c, d, e, f, g, h) do{if(a){b;c;d;e;f;g;h;}}while(0)
#  define GRD8(a, b, c, d, e, f, g, h, i) do{if(a){b;c;d;e;f;g;h;i;}}while(0)
# endif

# include <stddef.h>
# include <stdint.h>

# define ARR_GROW_FACTOR 2
# define ARR_INDEX(a, b) ((void *)(((uint8_t *)(a)->arr) + ((b) * (a)->elm)))

typedef struct	s_arr
{
	void		*arr;
	size_t		elm;
	size_t		len;
	size_t		cap;
}				t_arr;

int8_t			arr_init(t_arr *src, size_t cap, size_t elm);
void			arr_dtr(t_arr *src);
int8_t			arr_reserve(t_arr *src, size_t sze);
int8_t			arr_insertat(t_arr *dst, size_t i, const void *src
							, size_t src_len);
int8_t			arr_removeat(t_arr *src, size_t i, size_t len);
void			arr_swap(t_arr *src, size_t i, size_t j);
void			arr_reverse(t_arr *src);
void			arr_qsort(t_arr *src, int (*cmp)(const void *, const void *
							, size_t));
void			arr_qsort_r(t_arr *src, void *thunk, int (*cmp)(const void *
							, const void *, size_t, void *));
char			*arr_tostr(t_arr *src);

#endif

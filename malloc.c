/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:41:24 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/16 13:29:08 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memfunctions.h"

static void			*tiny_function(size_t size)
{
	t_allocated		*tmp;

	tmp = struct_manager(&(g_all_alloc.tiny_lst), size, getpagesize(), 0);
	return (tmp->alloc);
}

static void			*small_function(size_t size)
{
	t_allocated		*tmp;

	tmp = struct_manager(&(g_all_alloc.small_lst), size, getpagesize() * 100, 0);
	return (tmp->alloc);
}

static void			*large_function(size_t size)
{
	t_allocated		*tmp;

	tmp = struct_manager(&(g_all_alloc.large_lst), size, size, 1);
	return (tmp->alloc);
}

void				*malloc(size_t size)
{
	write(1, "my malloc\n", 10);
    show_alloc_mem();
    write(1, "\n", 1);
	if (size <= TINY)
		return (tiny_function(size));
	else if (size <= SMALL)
		return (small_function(size));
	else
		return (large_function(size));
}

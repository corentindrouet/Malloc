/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:41:24 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/15 11:18:46 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memfunctions.h"

static t_allocated	*new_t_allocated(size_t size, t_allocated *base, void *map,
						size_t map_max_size)
{
	t_allocated		*tmp;

	tmp = NULL;
	if (!base)
		tmp = map;
	else
	{
		tmp = base;
		while (tmp->next && (!tmp->free || tmp->size < size))
			tmp = tmp->next;
		if (tmp->free)
		{
			tmp->free = 0;
			return (tmp);
		}
		if (((map + map_max_size) - (((void*)(tmp + 1)) + tmp->size)) <
				(long)(map_max_size / 128))
			return (NULL);
		tmp->next = ((void*)(tmp + 1) + tmp->size);
		tmp = tmp->next;
	}
	tmp->size = size;
	tmp->free = 0;
	tmp->next = NULL;
	return (tmp);
}

static void			*tiny_function(size_t size)
{
	t_allocated		*tmp;

	tmp = NULL;
	errno = 0;
	if (!g_all_alloc.tiny)
		g_all_alloc.tiny = mmap(0, getpagesize(), PROT_READ |
				PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (errno)
		return (NULL);
	if (!g_all_alloc.tiny_lst)
	{
		g_all_alloc.tiny_lst = new_t_allocated(size, NULL,
				g_all_alloc.tiny, (TINY + STRUCT_SIZE) * 128);
		tmp = g_all_alloc.tiny_lst;
	}
	else
		tmp = new_t_allocated(size, g_all_alloc.tiny_lst,
			g_all_alloc.tiny, (TINY + STRUCT_SIZE) * 128);
	return (tmp + 1);
}

static void			*small_function(size_t size)
{
	t_allocated		*tmp;

	tmp = NULL;
	errno = 0;
	if (!g_all_alloc.small)
	{
		g_all_alloc.small = mmap(0, getpagesize() * 8, PROT_READ |
				PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	}
	if (errno)
		return (NULL);
	if (!g_all_alloc.small_lst)
	{
		g_all_alloc.small_lst = new_t_allocated(size, NULL,
				g_all_alloc.small, (SMALL + STRUCT_SIZE) * 128);
		tmp = g_all_alloc.small_lst;
	}
	else
		tmp = new_t_allocated(size, g_all_alloc.small_lst,
			g_all_alloc.small, (SMALL + STRUCT_SIZE) * 128);
	show_alloc_mem();
	return (tmp + 1);
}

static void			*large_function(size_t size)
{
	t_allocated		*tmp;
	t_allocated		*ptr_lst;

	ptr_lst = g_all_alloc.large_lst;
	if (ptr_lst)
		while (ptr_lst->next)
			ptr_lst = ptr_lst->next;
	tmp = mmap(0, size + STRUCT_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!ptr_lst)
		ptr_lst = tmp;
	else
		ptr_lst->next = tmp;
	tmp->size = size;
	tmp->free = 0;
	tmp->next = NULL;
	return (tmp + 1);
}

void				*malloc(size_t size)
{
	write(1, "my malloc\n", 10);
	if (size <= TINY)
		return (tiny_function(size));
	else if (size <= SMALL)
		return (small_function(size));
	else
		return (large_function(size));
}

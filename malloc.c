/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:41:24 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/13 14:01:11 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memfunction.h"

static t_allocated	*new_t_allocated(size_t size, t_allocated *base, void *map,
						size_t map_max_size)
{
	t_allocated		*tmp;

	tmp = NULL;
	if (!base)
		tmp = map;
	else
	{
		while (base->next && base->free)
			base = base->next;
		if ((map_max_size - ((void*)(base + 1) + base->size)) <
				(map_max_size / 100))
			return (NULL);
		base->next = ((void*)(base + 1) + base->size);
		tmp = base->next;
	}
	tmp->size = size;
	tmp->free = 0;
	tmp->next = NULL;
	return (tmp);
}

static void			*tiny_function(size_t size)
{
	static void		*tiny = NULL;
	t_allocated		*tmp;

	tmp = NULL;
	errno = 0;
	if (!tiny)
		tiny = mmap(0, getpagesize() * 100, PROT_READ |
				PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (errno)
		return (NULL);
	if (!g_all_alloc.tiny_lst)
	{
		g_all_alloc.tiny_lst = new_t_allocated(size, g_all_alloc.tiny_lst,
				tiny, (TINY + STRUCT_SIZE) * 100);
		tmp = g_all_alloc.tiny_lst;
	}
	tmp = new_t_allocated(size, g_all_alloc.tiny_lst, tiny,
			(TINY + STRUCT_SIZE) * 100);
	return (tmp + 1);
}

static void			*small_function(size_t size)
{
	static void		*small = NULL;
	t_allocated		*tmp;

	tmp = NULL;
	errno = 0;
	if (!small)
		small = mmap(0, (getpagesize() * 8) * 100, PROT_READ |
				PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (errno)
		return (NULL);
	if (!g_all_alloc.tiny_lst)
	{
		g_all_alloc.tiny_lst = new_t_allocated(size, g_all_alloc.small_lst,
				small, (SMALL + STRUCT_SIZE) * 100);
		tmp = g_all_alloc.small_lst;
	}
	tmp = new_t_allocated(size, g_all_alloc.small_lst, small,
			(SMALL + STRUCT_SIZE) * 100);
	return (tmp + 1);
}

static void			large_function(size_t size)
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
	tmp->free = false;
	tmp->next = NULL;
	return (tmp + 1);
}

void				*malloc(size_t size)
{
	if (size <= TINY)
		return (tiny_function(size));
	else if (size <= SMALL)
		return (small_function(size));
	else
		return (large_function(size));
}

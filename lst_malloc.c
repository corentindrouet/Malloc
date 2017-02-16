/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 09:19:33 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/16 14:05:40 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memfunctions.h"

static t_allocated	*init_lst(size_t size, size_t map_max_size)
{
	t_allocated	*tmp;

	tmp = mmap(0, getpagesize(), PROT_READ |
			PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->size = size;
	tmp->free = 0;
	tmp->page_total_size = size;
	tmp->struct_page_total_size = STRUCT_SIZE;
	tmp->alloc = mmap(0, map_max_size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->next = NULL;
	tmp->previous = NULL;
	return (tmp);
}

static void			*memory_address(t_allocated *lst, size_t map_max_size,
		short is_large)
{
	if (is_large || ((lst->previous->page_total_size + lst->size) > map_max_size))
		return (mmap(0, map_max_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0));
	else
		return (lst->previous->alloc + lst->previous->size);
}

static void			check_struct_page_size(t_allocated *lst)
{
	if ((int)(lst->struct_page_total_size + STRUCT_SIZE) > getpagesize())
	{
		lst->next = mmap(0, getpagesize(), PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		lst->next->struct_page_total_size = STRUCT_SIZE;
	}
	else
		lst->next = (lst + 1);
}

int					check_for_free(t_allocated *lst, size_t size,
		short is_large)
{
	if (!lst->free)
		return (0);
	if (lst->free && !is_large && lst->size >= size)
	{
		lst->free = 0;
		return (1);
	}
	if (lst->free && is_large)
	{
		lst->size = size;
		lst->page_total_size = size;
		lst->alloc = memory_address(lst, size, is_large);
		lst->free = 0;
		return (1);
	}
	return (0);
}

t_allocated			*struct_manager(t_allocated **lst, size_t size,
		size_t map_max_size, short is_large)
{
	t_allocated	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = init_lst(size, map_max_size);
		return (*lst);
	}
	while (tmp->next && (!tmp->free || tmp->size < size))
		tmp = tmp->next;
	if (check_for_free(tmp, size, is_large))
		return (tmp);
	check_struct_page_size(tmp);
	tmp->next->previous = tmp;
	tmp = tmp->next;
	tmp->size = size;
	tmp->page_total_size = tmp->previous->page_total_size + size;
	tmp->free = 0;
	if (tmp->struct_page_total_size != STRUCT_SIZE)
		tmp->struct_page_total_size =
			tmp->previous->struct_page_total_size + STRUCT_SIZE;
	tmp->alloc = memory_address(tmp, map_max_size, is_large);
	return (tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:26:22 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/21 14:19:30 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

static void			defrag(t_allocated **lst, t_allocated *maillon)
{
	t_allocated	*tmp;
	t_allocated	*next_maillon;
	int			nb_not_free;

	while (maillon->previous && maillon->page_total_size != maillon->size)
		maillon = maillon->previous;
	tmp = maillon;
	nb_not_free = 0;
	if (!maillon->free)
		nb_not_free++;
	maillon = maillon->next;
	while (!nb_not_free && maillon->next
			&& maillon->page_total_size != maillon->size)
	{
		if (!maillon->free)
			nb_not_free++;
		maillon = maillon->next;
	}
	next_maillon = maillon;
	if (!nb_not_free)
	{
		if (tmp == *lst)
		{
			if (tmp->size > SMALL)
				munmap((void*)tmp->alloc, tmp->size);
			else
				munmap((void*)tmp->alloc, ((tmp->size <= TINY) ? TINY : SMALL));
			*lst = next_maillon;
			if (next_maillon)
				next_maillon->previous = NULL;
		}
		else
		{
			maillon = tmp->previous;
			maillon->next = next_maillon;
			if (next_maillon)
				next_maillon->previous = maillon;
			if (tmp->size > SMALL)
				munmap((void*)tmp->alloc, tmp->size);
			else
				munmap((void*)tmp->alloc, ((tmp->size <= TINY) ? TINY : SMALL));
		}
	}
}

t_allocated			*search_ptr_lst(t_allocated *lst, void *ptr)
{
	t_allocated	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	while (tmp->alloc != ptr)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if (tmp->alloc == ptr)
		return (tmp);
	return (NULL);
}

void				free(void *ptr)
{
	t_allocated	*tmp;
	int			inc;
	void		*struct_alloc;

	if (!ptr)
		return ;
	struct_alloc = &g_all_alloc;
	inc = 0;
	while (inc < 3)
	{
		tmp = *((t_allocated**)(struct_alloc + (sizeof(t_allocated*) * inc)));
		tmp = search_ptr_lst(tmp, ptr);
		if (inc == 2 && tmp)
		{
			munmap(tmp->alloc, tmp->size);
			tmp->alloc = NULL;
			tmp->free = 1;
		}
		else if (tmp)
		{
			tmp->free = 1;
			defrag(((t_allocated**)(struct_alloc + (sizeof(t_allocated*) * inc))), tmp);
			break ;
		}
		inc++;
	}
}

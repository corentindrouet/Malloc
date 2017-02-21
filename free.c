/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:26:22 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/21 15:08:43 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

static void			delete_element(t_allocated **lst, t_allocated *elem,
		t_allocated *start)
{
	t_allocated	*next_maillon;

	next_maillon = elem;
	elem = start->previous;
	if (start == *lst)
		*lst = next_maillon;
	else
		elem->next = next_maillon;
	if (next_maillon)
		next_maillon->previous = elem;
}

static void			delete_map(t_allocated *tmp)
{
	if (tmp->size > SMALL)
	{
		munmap((void*)tmp->alloc, tmp->size);
		tmp->alloc = NULL;
	}
	else
		munmap((void*)tmp->alloc, ((tmp->size <= TINY) ? TINY : SMALL));
}

static void			defrag(t_allocated **lst, t_allocated *maillon)
{
	t_allocated	*tmp;
	int			nb_not_free;

	while (maillon->previous && maillon->page_total_size != maillon->size)
		maillon = maillon->previous;
	tmp = maillon;
	nb_not_free = 0;
	if (!maillon->free)
		nb_not_free++;
	maillon = maillon->next;
	while (!nb_not_free && maillon
			&& maillon->page_total_size != maillon->size)
	{
		if (!maillon->free)
			nb_not_free++;
		maillon = maillon->next;
	}
	if (!nb_not_free)
	{
		delete_element(lst, maillon, tmp);
		delete_map(tmp);
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
	t_allocated	**lst;
	int			inc;
	void		*struct_alloc;

	if (!ptr)
		return ;
	struct_alloc = &g_all_alloc;
	inc = 0;
	while (inc < 3)
	{
		lst = ((t_allocated**)(struct_alloc + (sizeof(t_allocated*) * inc)));
		tmp = *lst;
		tmp = search_ptr_lst(tmp, ptr);
		if (tmp)
		{
			tmp->free = 1;
			defrag(lst, tmp);
			break ;
		}
		inc++;
	}
}

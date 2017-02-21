/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:26:22 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/21 09:06:16 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
		}
		if (tmp)
		{
			tmp->free = 1;
			break ;
		}
		inc++;
	}
}

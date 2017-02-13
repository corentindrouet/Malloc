/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:30:48 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/13 14:20:47 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memfunctions.h"

void	*realloc(void *ptr, size_t size)
{
	t_allocated	*tmp;
	int			inc;
	void		*struct_alloc;

	if (!ptr)
		return malloc(size);
	struct_alloc = g_all_alloc;
	inc = 0;
	while (inc < 3)
	{
		tmp = (t_allocated*)(struct_alloc + (sizeof(t_allocated*) * inc));
		tmp = search_ptr_lst(tmp, ptr);
		if (tmp)
			break ;
		inc++;
	}
	if (!tmp)
		return NULL;
	if (tmp->size >= size)
		return tmp;
}

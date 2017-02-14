/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:26:22 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/14 15:56:42 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memfunctions.h"
#include <unistd.h>

t_allocated			*search_ptr_lst(t_allocated *lst, void *ptr)
{
	t_allocated	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	while ((tmp + 1) != ptr)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if ((tmp + 1) == ptr)
		return (tmp);
	return (NULL);
}

void				free(void *ptr)
{
	t_allocated	*tmp;
	int			inc;
	void		*struct_alloc;

    write(1, "free\n", 5);
	if (!ptr)
		return ;
	struct_alloc = &g_all_alloc;
	inc = 0;
	while (inc < 3)
	{
		tmp = *((t_allocated**)(struct_alloc + (sizeof(t_allocated*) * inc)));
        if (!g_all_alloc.tiny_lst)
            write(1, "- NO PTR -", 10);
		tmp = search_ptr_lst(tmp, ptr);
		if (inc == 2 && tmp)
			munmap((void*)(tmp + 1), tmp->size);
		else if (tmp)
		{
			tmp->free = 1;
			break ;
		}
		inc++;
	}
    write(1, "\n", 1);
	return ;
}

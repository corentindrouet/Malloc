/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:30:48 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/16 13:53:02 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memfunctions.h"
#include <unistd.h>

static void	*enough_space(t_allocated *ptr, size_t size)
{
	ptr->size = size;
	return (ptr->alloc);
}

static void	*not_enough_space(t_allocated *ptr, size_t size)
{
	char	*tmp;
	char	*ptr_content;
	size_t	i;

	ptr_content = (char*)(ptr->alloc);
	tmp = malloc(size);
	i = 0;
	while (i < ptr->size && i < size)
	{
		tmp[i] = ptr_content[i];
		i++;
	}
	ptr->free = 1;
	return (tmp);
}

static int	check_if_enough_space(t_allocated *ptr, size_t size)
{
	ft_putnbr(ptr->size);
	write(1, "-", 1);
	ft_putnbr(size);
	write(1, "\n", 1);
	if (ptr->size <= TINY && size > TINY)
		return (0);
	else if (ptr->size <= SMALL && (size > SMALL || size <= TINY))
		return (0);
	else if (ptr->size > SMALL && size <= SMALL)
		return (0);
	else if (ptr->next && ptr->size < size)
		return (0);
	return (1);
}

void		*realloc(void *ptr, size_t size)
{
	t_allocated	*tmp;
	int			inc;
	void		*struct_alloc;

	write(1, "realloc\n", 8);
	if (!ptr)
		return (malloc(size));
	struct_alloc = &g_all_alloc;
	inc = 0;
	while (inc < 3)
	{
		tmp = *((t_allocated**)(struct_alloc + (sizeof(t_allocated*) * inc)));
		tmp = search_ptr_lst(tmp, ptr);
		if (tmp)
			break ;
		inc++;
	}
	if (!tmp)
		return (NULL);
	if (check_if_enough_space(tmp, size))
		return (enough_space(tmp, size));
	return (not_enough_space(tmp, size));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 13:13:44 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/16 14:04:39 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memfunctions.h"

void	show_alloc_mem(void)
{
	t_allocated	*tmp;
	void		*all_alloc;
	int			i;

	all_alloc = &g_all_alloc;
	i = 0;
	while (i < 3)
	{
		tmp = *((t_allocated**)(all_alloc + (sizeof(t_allocated*) * i)));
		if (i == 0)
			ft_putstr("TINY: ");
		else if (i == 1)
			ft_putstr("SMALL");
		else
			ft_putstr("LARGE");
        if (tmp)
        {
            ft_putlnbr((long long)tmp->alloc);
            ft_putchar('\n');
        }
        else
            ft_putchar('\n');
		while (tmp)
		{
			ft_putstr("start: ");
			ft_putlnbr((long long)tmp->alloc);
			ft_putstr("  size: ");
			ft_putnbr(tmp->size);
			ft_putstr("  page_size: ");
			ft_putnbr(tmp->page_total_size);
			ft_putchar('\n');
			tmp = tmp->next;
		}
		i++;
	}
}

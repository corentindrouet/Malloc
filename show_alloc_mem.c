/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 13:13:44 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/16 15:49:34 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memfunctions.h"

void	show_alloc_mem(void)
{
	t_allocated	*tmp;
	void		*all_alloc;
	int			i;
    char        *str_tmp;

	all_alloc = &g_all_alloc;
	i = 0;
	while (i < 3)
	{
		tmp = *((t_allocated**)(all_alloc + (sizeof(t_allocated*) * i)));
		if (i == 0)
			ft_putstr("TINY: ");
		else if (i == 1)
			ft_putstr("SMALL : ");
		else
			ft_putstr("LARGE : ");
        if (tmp)
        {
            str_tmp = ft_ltoa_base((long)tmp->alloc, 16);
            ft_putendl(str_tmp);
            free(str_tmp);
        }
        else
            ft_putchar('\n');
		while (tmp)
		{
            if (!tmp->free)
            {
                str_tmp = ft_ltoa_base((long)tmp->alloc, 16);
                ft_putstr(str_tmp);
                free(str_tmp);
                ft_putstr(" - ");
                str_tmp = ft_ltoa_base((long)(tmp->alloc + tmp->size), 16);
                ft_putstr(str_tmp);
                free(str_tmp);
                ft_putstr(" : ");
                ft_putnbr(tmp->size);
                ft_putstr(" octets");
                ft_putchar('\n');
            }
			tmp = tmp->next;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 13:13:44 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/21 14:32:57 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	page_header(int index, t_allocated *tmp)
{
	char	*ltoa_str;

	if (index == 0)
		ft_putstr("TINY: ");
	else if (index == 1)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	if (tmp)
	{
		ltoa_str = ft_ltoa_base((long)tmp->alloc, 16);
		ft_putstr("0x");
		ft_putendl(ltoa_str);
		free(ltoa_str);
	}
	else
		ft_putchar('\n');
}

static void	print_alloc_infos(t_allocated *tmp)
{
	char	*ltoa_str;

	ltoa_str = ft_ltoa_base((long)tmp->alloc, 16);
	ft_putstr("    0x");
	ft_putstr(ltoa_str);
	free(ltoa_str);
	ft_putstr(" - ");
	ltoa_str = ft_ltoa_base((long)(tmp->alloc + tmp->size - 1), 16);
	ft_putstr("0x");
	ft_putstr(ltoa_str);
	free(ltoa_str);
	ft_putstr(" : ");
	ft_putnbr(tmp->size);
	ft_putstr(" octets");
	ft_putchar('\n');
}

void		show_alloc_mem(void)
{
	t_allocated	*tmp;
	void		*all_alloc;
	int			i;

	all_alloc = &g_all_alloc;
	i = 0;
	while (i < 3)
	{
		tmp = *((t_allocated**)(all_alloc + (sizeof(t_allocated*) * i)));
		page_header(i, tmp);
		while (tmp)
		{
            if (tmp->page_total_size == tmp->size)
                ft_putstr("  NEW PAGE\n");
			if (!tmp->free)
				print_alloc_infos(tmp);
			tmp = tmp->next;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memfunctions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 08:54:53 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/09 14:55:17 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMFUNCTIONS_H
# define MEMFUNCTIONS_H
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
# define TINY 4
# define SMALL 128
# define STRUCT_SIZE sizeof(struct s_allocated)

typedef struct			s_allocated
{
	size_t				size;
	int					free;
	struct s_allocated	*next;
}						t_allocated;

typedef struct			s_all_alloc
{
	t_allocated			*tiny_lst;
	t_allocated			*small_lst;
	t_allocated			*large_lst;
}						t_all_alloc;

static t_all_alloc		g_all_alloc;

void					*malloc(size_t size);

#endif

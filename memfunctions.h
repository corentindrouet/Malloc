/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memfunctions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 08:54:53 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/15 11:17:21 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMFUNCTIONS_H
# define MEMFUNCTIONS_H
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
# include <errno.h>
# include "libft.h"
# define STRUCT_SIZE sizeof(struct s_allocated)
# define TINY ((getpagesize() / 128) - STRUCT_SIZE)
# define SMALL (((getpagesize() * 8) / 128) - STRUCT_SIZE)

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
	void				*tiny;
	void				*small;
}						t_all_alloc;

t_all_alloc				g_all_alloc;

void					*malloc(size_t size);
void					free(void *ptr);
void					*realloc(void *ptr, size_t size);
t_allocated				*search_ptr_lst(t_allocated *lst, void *ptr);
void					show_alloc_mem();

#endif

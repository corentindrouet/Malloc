/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memfunctions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 08:54:53 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/21 09:08:05 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
# include <errno.h>
# include "libft/libft.h"
# define STRUCT_SIZE sizeof(struct s_allocated)
# define TINY 1024
# define SMALL (1024 * 100)

typedef struct			s_allocated
{
	size_t				size;
	int					free;
	size_t				page_total_size;
	size_t				struct_page_total_size;
	void				*alloc;
	struct s_allocated	*previous;
	struct s_allocated	*next;
}						t_allocated;

typedef struct			s_all_alloc
{
	t_allocated			*tiny_lst;
	t_allocated			*small_lst;
	t_allocated			*large_lst;
}						t_all_alloc;

t_all_alloc				g_all_alloc;

void					*malloc(size_t size);
void					free(void *ptr);
void					*realloc(void *ptr, size_t size);
t_allocated				*search_ptr_lst(t_allocated *lst, void *ptr);
void					show_alloc_mem(void);
t_allocated				*struct_manager(t_allocated **lst, size_t size,
							size_t map_max_size, short is_large);

#endif

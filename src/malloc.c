/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:18:14 by dmlitvin          #+#    #+#             */
/*   Updated: 2020/03/07 17:18:25 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone *g_zone = NULL;
int log_fd;

void	*malloc(const size_t size)
{
    t_zone *mem_zone;
	t_block *mem_block;
	void *memory;

	log_fd = open("logfile.txt", O_WRONLY);
	memory = NULL;
	mem_zone = get_suitable_zone(size);
	if ((mem_block = alloc_block(mem_zone, size)))
		memory = mem_block + 1;
	return (memory);
}

void	free(void *ptr)
{
    (void)ptr;
}

void	*realloc(void *ptr, size_t size)
{
    (void)ptr;
    (void)size;
	return (NULL);
}

void	show_alloc_mem(void)
{
}

void	show_alloc_mem_ex(void)
{
}

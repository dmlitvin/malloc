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

void	*malloc(const size_t size)
{
    t_zone *mem_zone;
	t_block *mem_block;
	void *memory;

	ft_putendl("entering malloc");
	memory = NULL;
	mem_zone = get_suitable_zone(size);
	ft_putstr("got suitable zone, ptr: ");
	ft_putnbr((size_t)mem_zone);
    ft_putstr("\n");
	if ((mem_block = alloc_block(mem_zone, size)))
		memory = mem_block + 1;
	ft_putstr("malloc return value: ");
	ft_putnbr((size_t)memory);
	ft_putstr("\n\n");
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

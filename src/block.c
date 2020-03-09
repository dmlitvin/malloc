/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:38:34 by dmlitvin          #+#    #+#             */
/*   Updated: 2020/03/09 14:38:37 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

bool is_placeable(t_zone *zone, const size_t size)
{
    t_block *block;
    size_t taken_space_size;
    size_t free_space_size;

    ft_putstr("is_placeable entering\n");
    block = zone->block_list;
    if (block)
    {
        ft_putstr("got in if (block)\n");
        while (block->next)
            block = block->next;
        ft_putstr("got last block\n");
        taken_space_size = (size_t)zone - (((size_t)block) + block->size);
        taken_space_size += sizeof(t_zone);
        ft_putstr("zone->size: ");
        ft_putnbr(zone->size);
        ft_putstr("\n");
        ft_putstr("taken_space_size: ");
        ft_putnbr(taken_space_size);
        ft_putstr("\n");
        free_space_size = zone->size - taken_space_size;
        ft_putstr("free_space_size: ");
        ft_putnbr(free_space_size);
        ft_putstr("\n");
        return free_space_size >= (size + sizeof(t_block));
    }
    return (size <= (zone->size - sizeof(t_zone) - sizeof(block)));
}

static t_block *write_block(t_block *place, t_block **place_to_save, const size_t size)
{
    ft_putendl("writing block meta info");
    *place_to_save = place;
    place->next = NULL;
    place->is_busy = true;
    place->size = size;
    ft_putendl("block meta info written");
    return place;
}

t_block *alloc_block(t_zone *zone, const size_t size)
{
    t_block *block;

    ft_putendl("alloc_block entering");
    block = zone->block_list;
    if (block)
    {
        ft_putendl("got in if (block)");
        while (block->next)
            block = block->next;
        ft_putendl("got last block");
        block = write_block((void*)(block + 1) + block->size, &block->next, size);
    }
    else
        block = write_block(zone->memory + sizeof(t_zone), &zone->block_list, size);
    return (block);
}

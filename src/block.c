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

    block = zone->block_list;
    if (block)
    {
        while (block->next)
            block = block->next;
        taken_space_size = (size_t)zone - (((size_t)block) + block->size);
        taken_space_size += sizeof(t_zone);
        free_space_size = zone->size - taken_space_size;
        return free_space_size >= (size + sizeof(t_block));
    }
    return (size <= (zone->size - sizeof(block)));
}

static t_block *place_block(t_block *place, t_block **place_to_save, const size_t size)
{
    *place_to_save = place;
    place->next = NULL;
    place->is_busy = true;
    place->size = size;
    return place;
}

t_block *alloc_block(t_zone *zone, const size_t size)
{
    t_block *block;

    block = zone->block_list;
    if (block)
    {
        while (block->next)
            block = block->next;
        block = place_block((void*)(block + 1) + block->size, &block->next, size);
    }
    else
        block = place_block(zone->memory + sizeof(t_zone), &zone->block_list, size);
    return (block);
}

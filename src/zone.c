/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:38:19 by dmlitvin          #+#    #+#             */
/*   Updated: 2020/03/09 14:38:21 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <sys/mman.h>

t_zone *g_zone;

static enum e_zone get_suitable_zone_type(const size_t size)
{
    enum e_zone zone_type;

    if (size <= N)
        zone_type = TINY;
    else if (size < M)
        zone_type = SMALL;
    else
        zone_type = LARGE;
    return (zone_type);
}

static t_zone *find_suitable_zone(const enum e_zone zone_type, const size_t size)
{
    t_zone *zone_ptr;

    zone_ptr = g_zone;
    while (zone_ptr)
    {
        zone_ptr = zone_ptr->next;
        if (zone_ptr->type == zone_type && is_placeable(zone_ptr, size))
            break ;
    }
    return (zone_ptr);
}

static void write_zone(t_zone *zone, const enum e_zone zone_type, const size_t zone_size)
{
    zone->block_list = NULL;
    zone->memory = zone;
    zone->next = NULL;
    zone->size = zone_size;
    zone->type = zone_type;
}

static t_zone *allocate_zone(const enum e_zone zone_type, size_t block_size)
{
    t_zone *zone;
    size_t allocating_size;
    size_t block_count;

    if (zone_type == LARGE)
        block_count = 1;
    else if (zone_type == SMALL)
    {
        block_size = M;
        block_count = 100;
    }
    else
    {
        block_size = N;
        block_count = 100;
    }
    allocating_size = sizeof(t_zone) + ((sizeof(t_block) + block_size) * block_count);
    zone = mmap(NULL, allocating_size, PROT_WRITE | PROT_READ, MAP_ANON, -1, 0);
    if (zone)
        write_zone(zone, zone_type, allocating_size);
    return (zone);
}

t_zone *get_suitable_zone(const size_t size)
{
    const enum e_zone zone_type = get_suitable_zone_type(size);
    t_zone *zone;

    zone = find_suitable_zone(zone_type, size);
    if (NULL == zone)
    {
        zone = allocate_zone(zone_type, size);
        zone->next = g_zone;
        g_zone = zone;
    }
    return (zone);
}

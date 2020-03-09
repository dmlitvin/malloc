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

    ft_putstr("find_suitable_zone entering\n");
    zone_ptr = g_zone;
    while (zone_ptr)
    {
        if (zone_ptr->type == zone_type && is_placeable(zone_ptr, size))
            break ;
        zone_ptr = zone_ptr->next;
    }
    return (zone_ptr);
}

static void write_zone(t_zone *zone, const enum e_zone zone_type, const size_t zone_size)
{
    ft_putendl("writing zone meta info");
    zone->block_list = NULL;
    zone->memory = zone;
    zone->next = NULL;
    zone->size = zone_size;
    zone->type = zone_type;
    ft_putendl("written zone meta info");
}

static t_zone *allocate_zone(const enum e_zone zone_type, size_t block_size)
{
    t_zone *zone;
    size_t allocating_size;
    size_t block_count;

    ft_putendl("allocate_zone entering");
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
    ft_putstr("allocating_size: ");
    allocating_size = sizeof(t_zone) + ((sizeof(t_block) + block_size) * block_count);
    ft_putnbr(allocating_size);
    zone = mmap(NULL, allocating_size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
    ft_putstr("\n");
    ft_putstr("mapped zone ptr: ");
    ft_putnbr((size_t)zone);
    ft_putstr("\n");
    if (zone)
        write_zone(zone, zone_type, allocating_size);
    return (zone);
}

t_zone *get_suitable_zone(const size_t size)
{
    const enum e_zone zone_type = get_suitable_zone_type(size);
    t_zone *zone;

    ft_putstr("get_suitable_zone entering\n");
    ft_putstr("zone_type: ");
    ft_putnbr(zone_type);
    ft_putstr("\n");
    ft_putstr("block size: ");
    ft_putnbr(size);
    ft_putstr("\n");
    zone = find_suitable_zone(zone_type, size);
    if (NULL == zone)
    {
        ft_putendl("got in if (NULL == zone)");
        zone = allocate_zone(zone_type, size);
        zone->next = g_zone;
        g_zone = zone;
    }
    return (zone);
}

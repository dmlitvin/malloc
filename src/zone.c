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

t_zone *g_zone;

enum e_zone get_suitable_zone_size(const size_t size)
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

t_zone *find_suitable_zone(const enum e_zone zone_type, const size_t size)
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

t_zone *allocate_zone(const enum e_zone zone_type)
{
    (void)zone_type;
    return (NULL);
}

t_zone *get_suitable_zone(const size_t size)
{
    const enum e_zone zone_type = get_suitable_zone_size(size);

    t_zone *zone;
    
    zone = find_suitable_zone(zone_type, size);
    if (NULL == zone)
        zone = allocate_zone(zone_type);
    return (zone);
}

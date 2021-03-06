/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stralloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 17:33:15 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/12 15:46:29 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stralloc(size_t size)
{
	char *out;

	if ((out = malloc(size + 1)))
		out[size] = 0;
	return (out);
}

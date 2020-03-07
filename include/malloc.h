/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:17:06 by dmlitvin          #+#    #+#             */
/*   Updated: 2020/03/07 17:17:38 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>
# include <unistd.h>

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t new_size);
void show_allow_mem(void);
void show_allow_mem_ex(void);

#endif

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
# include <stdbool.h>

# define N 128
# define M 512

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t new_size);
void show_alloc_mem(void);
void show_alloc_mem_ex(void);

enum e_zone
{
    TINY,
    SMALL,
    LARGE
};

typedef struct s_block
{
    struct s_block *next;
    bool is_busy;
    size_t size;
} t_block;

typedef struct s_zone
{
    struct s_zone *next;
    void *memory;
    enum e_zone type;
    size_t size;
    t_block *block_list;
} t_zone;

extern t_zone *g_zone;

t_zone *get_suitable_zone(const size_t size);
t_block *alloc_block(t_zone *zone, const size_t size);
bool is_placeable(t_zone *zone, const size_t size);

#include <fcntl.h>

extern int log_fd;

#endif

/*
    # void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
    # int munmap(void *addr, size_t len);
    # int getpagesize(void);
    # int getrlimit(int resource, struct rlimit *rlp);
*/

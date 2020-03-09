# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/07 15:58:12 by dmlitvin          #+#    #+#              #
#    Updated: 2020/03/07 15:58:16 by dmlitvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC=clang
REMOVE=rm -rf

LFTBIN=libft/libft.a

MALLOC=libft_malloc_$(HOSTTYPE).so

MALLOC_SRC=malloc.c zone.c block.c

SRC=$(addprefix src/, $(MALLOC_SRC))

SRO=$(SRC:.c=.o)

all: $(MALLOC)

$(MALLOC): $(LFTBIN) $(SRO)
	@$(CC) -shared -o $(MALLOC) $(SRO)
	@strip -x $(MALLOC)
	@ln -sf $(MALLOC) libft_malloc.so

$(LFTBIN):
	@make -j -C libft

%.o: %.c include/malloc.h
	@$(CC) -c -I libft/include -I include -Wall -Wextra -Werror -fPIC $< -o $@

clean:
	@$(REMOVE) $(SRO)
	@make -j clean -C libft

fclean: clean
	@$(REMOVE) $(MALLOC)
	@$(REMOVE) libft_malloc.so
	@make -j fclean -C libft

re: fclean all

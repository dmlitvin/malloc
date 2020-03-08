# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/08 17:48:23 by dmlitvin          #+#    #+#              #
#    Updated: 2020/03/08 17:48:24 by dmlitvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

if [ $(uname -s) = Darwin ]
then
	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES="libft_malloc.so"
	export DYLD_FORCE_FLAT_NAMESPACE=1
	$@
else
	export LD_LIBRARY_PATH=.
	export LD_PRELOAD=./libft_malloc.so
	$@
fi

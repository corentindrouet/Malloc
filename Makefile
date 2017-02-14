# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/24 08:17:02 by cdrouet           #+#    #+#              #
#    Updated: 2017/02/14 12:05:29 by cdrouet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so
CC= gcc
CFLAGS= -Wall -Werror -Wextra
SRC_NAME= malloc.c \
					free.c \
					realloc.c
SRC_PATH= ./
INC_PATH=./
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(SRC) $(OBJ)
	gcc -shared -o $(NAME) $(OBJ)
	ln -s $(NAME) libft_malloc.so

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) -I$(INC_PATH) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)

.PHONY: fclean
fclean: clean
	rm -fv $(NAME) libft_malloc.so

.PHONY: re
re: fclean all

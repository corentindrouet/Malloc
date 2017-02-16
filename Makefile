# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/24 08:17:02 by cdrouet           #+#    #+#              #
#    Updated: 2017/02/16 13:12:24 by cdrouet          ###   ########.fr        #
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
					realloc.c \
					show_alloc_mem.c \
					lst_malloc.c
SRC_PATH= ./
INC_PATH=./
LIBFT_INC=./libft/
LIBFT_NAME=libftprintf.a
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIBFT_INC), $(LIBFT_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	gcc -shared -o $(NAME) $(OBJ) -L$(LIBFT_INC) -lftprintf
	ln -f -s $(NAME) libft_malloc.so

$(LIB):
	make -C $(LIBFT_INC)

.PHONY: libft
libft:
	make re -C $(LIBFT_INC)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) -I$(INC_PATH) -I$(LIBFT_INC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	make -C libft/ clean
	rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)

.PHONY: fclean
fclean: clean
	make -C libft/ fclean
	rm -fv $(NAME) libft_malloc.so

.PHONY: re
re: fclean all

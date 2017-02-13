# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/24 08:17:02 by cdrouet           #+#    #+#              #
#    Updated: 2017/02/13 14:22:00 by cdrouet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= avm
CC= gcc
CFLAGS= -Wall -Werror -Wextra -stdlib=libc++ -std=c++0x
SRC_NAME= malloc.c \
					free.c \
					realloc.c \
SRC_PATH= ./
INC_PATH= ./
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(SRC) $(OBJ)
	$(CC) $(CFLAGS)  -I$(INC_PATH) -o $(NAME) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) -I$(INC_PATH) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)

.PHONY: fclean
fclean: clean
	rm -fv $(NAME)

.PHONY: re
re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/24 08:17:02 by cdrouet           #+#    #+#              #
#    Updated: 2017/02/07 09:44:10 by cdrouet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= avm
CC= clang++
CFLAGS= -Wall -Werror -Wextra -stdlib=libc++ -std=c++0x
SRC_NAME= main.cpp \
		  Factory.class.cpp \
		  AsmOperator.class.cpp \
		  ExecFile.class.cpp \
		  instruction.class.cpp
SRC_PATH= ./sources/
INC_PATH= ./includes/
OBJ_NAME= $(SRC_NAME:.cpp=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(SRC) $(OBJ)
	$(CC) $(CFLAGS)  -I$(INC_PATH) -o $(NAME) $(OBJ) -stdlib=libc++ -std=c++0x

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
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

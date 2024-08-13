# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/30 20:32:52 by bel-barb          #+#    #+#              #
#    Updated: 2024/07/16 00:44:15 by bel-barb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror 
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
NAME = fractol
SRC = fract-ol.c atof.c helpers/helpers.c helpers/parsing.c helpers/helpers3.c helpers/parsing2.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%o: %c fractol.h
	$(CC) $(FLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLXFLAGS) -o $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/30 20:32:52 by bel-barb          #+#    #+#              #
#    Updated: 2024/07/08 22:56:39 by bel-barb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = fractol
SRC = fract-ol.c atof.c helpers.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -lmlx -framework OpenGL -framework AppKit -o $(NAME) -O3

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all claen re

#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otiniako <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/02 16:17:52 by otiniako          #+#    #+#              #
#    Updated: 2018/07/02 16:17:53 by otiniako         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

FLAGS = -Wall -Wextra -Werror -I includes/

LIB = libft/libft.a

SRC = src/lem_in.c\
		src/ft_valid.c\
		src/ft_ways.c\
		src/ft_turn.c\
		src/ft_lem.c\
		src/ft_go.c\
		src/ft_tools.c\
		src/ft_flags.c\

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	@make -C libft/

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(LIB)
	@echo "\033[1;92mlem_in are created!\033[m"

$(OBJ): %.o: %.c
	@gcc -c $(FLAGS) -o $@ -c $<

clean:
	@make -C libft/ clean
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all
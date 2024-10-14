# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarsa-s <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 16:30:44 by mmarsa-s          #+#    #+#              #
#    Updated: 2024/09/30 16:30:48 by mmarsa-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = main.c utils.c init.c POS_utils.c routine.c table.c

FLAGS = -Wall -Wextra -Werror -g -O3 -pthread -O0

HEADER = ./philo.h

SANITIZER = -fsanitize=thread

.PHONY: all clean fclean

all: $(NAME)

$(NAME): $(SRC) $(HEADER) $(MAKEFILE)
	@cc $(FLAGS) -o $(NAME) $(SRC) $(SANITIZER)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

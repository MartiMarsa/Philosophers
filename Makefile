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

# Colors

RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
RESET	= \033[0

NAME = philo

SRC = main.c utils.c init.c POS_utils.c routine.c table.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -O3 -pthread

HEADER = ./philo.h

# SANITIZER = -fsanitize=thread

.PHONY: all clean fclean

all: $(NAME)

$(NAME): $(OBJ) Makefile
	@cc $(CFLAGS) -o $(NAME) $(OBJ) $(SANITIZER)
	@echo "$(GREEN)Executable $(NAME) created$(RESET)"

%.o: %.c $(HEADER)
	@cc $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling $<$(RESET)"

clean:
	@rm -f $(OBJ)
	@echo "$(RED)Object files deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Executable $(NAME) deleted$(RESET)"

re: fclean all

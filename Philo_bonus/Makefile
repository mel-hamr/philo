# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/10 14:36:09 by mel-hamr          #+#    #+#              #
#    Updated: 2021/07/16 16:33:40 by mel-hamr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
SRCS = philo_bonus.c philo_bonus_utils.c ft_atoi.c utils.c forks.c
OBJS = $(SRCS:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror
%.o:%.c *.h
	$(CC) $(FLAGS) -c $< -o $@
all: *.h
	@$(MAKE) $(NAME)
$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
clean:
	rm -rf *.o
fclean:clean
	rm -rf $(NAME)
re: fclean all
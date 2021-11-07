# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/10 14:36:38 by mel-hamr          #+#    #+#              #
#    Updated: 2021/07/12 14:07:07 by mel-hamr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = philo.c philo_util.c ft_atoi.c intial.c 
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
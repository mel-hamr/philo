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
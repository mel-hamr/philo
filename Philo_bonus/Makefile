NAME = philo_bonus
SRCS = Philo_bonus.c philo_bonus_utils.c
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
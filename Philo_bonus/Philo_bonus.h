#ifndef PHILO_BONUS
#define PHILO_BONUS
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

#define SEMA_FORK "sema fork"
#define SEMA_PRINT "sema print"
#define SEMA_MAIN "sema main"


struct s_philo
{
	int 			index;
	struct s_vars	*vars;
	long			time_left_die;
	int				right_fork;
	int				meal_nbr;
}typedef t_philo;

struct s_vars
{
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				nbr_philo;
	long			start_time;
	int				nbr_must_eat;
	int				*pid;
	int				index;
	sem_t			*forks;
	sem_t			*main_sem;
	sem_t			*print_sem;
	t_philo			*philo;
}typedef t_vars;

#endif
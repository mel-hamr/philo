/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:57:44 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/16 16:33:34 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>

# define SEMA_FORK "sema fork"
# define SEMA_PRINT "sema print"
# define SEMA_MAIN "sema main"
# define SEMA_EAT	"sema eat"
# define SEMA_PHILO	"sema philo"

typedef struct s_philo
{
	int				index;
	struct s_vars	*vars;
	long			time_left_die;
	int				right_fork;
	int				eated;
	int				meal_nbr;
	sem_t			*sem_philo;
}	t_philo;

typedef struct s_vars
{
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				nbr_philo;
	long			start_time;
	int				nbr_must_eat;
	int				*pid;
	int				philo_finished;
	int				index;
	sem_t			*forks;
	sem_t			*main_sem;
	sem_t			*print_sem;
	sem_t			*eat_sem;
	t_philo			*philo;
}	t_vars;

int		check_arg(int ac, char **av);
void	intial_vars(char **av, t_vars *vars, int ac);
long	get_time(void);
int		intial_process(t_vars *vars, int i);
void	printf_text(t_vars *vars, t_philo *philo, char *msg);
int		ft_atoi(const char *str, int *error);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
void	unlock_forks(t_vars *vars);
void	lock_forks(t_philo *philo, t_vars *vars);
#endif

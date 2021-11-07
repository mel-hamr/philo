/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 07:51:44 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/17 07:51:45 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				index;
	struct s_vars	*vars;
	long			time_left_die;
	int				right_fork;
	int				meal_nbr;
	int				is_full;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_vars
{
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				nbr_philo;
	long			start_time;
	int				nbr_must_eat;
	int				philo_finished_eating;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	main_mutex;
	t_philo			*philo;
}	t_vars;

int		ft_atoi(const char *str, int *error);
t_vars	*vars_init(int ac, char **av);
long	get_time(void);
void	printf_text(t_philo *philo, t_vars *vars, char *msg);
int		ft_free(t_vars *vars);
void	initial_philo(t_vars *vars, int i);
void	*check_if_finished_eating(void *arg);
int		check_arg(int ac, char **av);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:57:08 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/05 17:25:45 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->fork[philo->index]);
	printf_text(philo, vars, "take a fork");
	pthread_mutex_lock(&vars->fork[(philo->index + 1) % vars->nbr_philo]);
	printf_text(philo, vars, "take a the right fork");
}

void	*watch_hem_die(void *arg)
{
	long	time;
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	while (1)
	{
		time = get_time();
		if (time > philo->time_left_die)
		{
			pthread_mutex_lock(&philo->vars->mutex_print);
			printf("die %d\n", philo->index + 1);
			pthread_mutex_unlock(&philo->vars->main_mutex);
		}
		if (philo->meal_nbr == vars->nbr_must_eat)
		{
			check_if_finished_eating(philo, vars);
		}
		usleep(500);
	}
	return (NULL);
}

void	routine(t_philo *philo, t_vars *vars)
{
	printf_text(philo, vars, "is eating");
	philo->time_left_die = get_time() + vars->time_to_die;
	usleep(vars->time_to_eat * 1000);
	philo->meal_nbr++;
	pthread_mutex_unlock(&vars->fork[philo->index]);
	pthread_mutex_unlock(&vars->fork[philo->right_fork]);
	printf_text(philo, vars, "is sleeping");
	usleep(vars->time_to_sleep * 1000);
	printf_text(philo, vars, "is thinking");
}

void	*simulation(void *arg)
{
	t_philo		*philo;
	t_vars		*vars;
	long		time;
	pthread_t	th;

	philo = (t_philo *)arg;
	vars = philo->vars;
	philo->time_left_die = get_time() + vars->time_to_die;
	pthread_create(&th, NULL, &watch_hem_die, philo);
	pthread_detach(th);
	while (1)
	{
		lock_forks(philo, vars);
		routine(philo, vars);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_vars			*vars;
	int				i;
	pthread_t		th;

	vars = vars_init(ac, av);
	i = 0;
	while (i < vars->nbr_philo)
	{
		pthread_mutex_init(&vars->fork[i], NULL);
		initial_philo(vars, i);
		i++;
	}
	i = 0;
	while (i < vars->nbr_philo)
	{
		pthread_create(&th, NULL, &simulation, &vars->philo[i]);
		i++;
		pthread_detach(th);
		usleep(100);
	}
	pthread_mutex_lock(&vars->main_mutex);
	return (ft_free(vars));
}

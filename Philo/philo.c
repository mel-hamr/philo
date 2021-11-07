/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:57:08 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/16 17:27:43 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->fork[philo->index]);
	printf_text(philo, vars, "has taken a fork");
	pthread_mutex_lock(&vars->fork[philo->right_fork]);
	printf_text(philo, vars, "has taken a fork");
}

void	*watch_hem_die(void *arg)
{
	long	time;
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	philo->time_left_die = get_time() + vars->time_to_die;
	while (1)
	{
		time = get_time();
		pthread_mutex_lock(&philo->mutex);
		if (time > philo->time_left_die
			&& philo->meal_nbr != vars->nbr_must_eat)
		{
			pthread_mutex_lock(&philo->vars->mutex_print);
			printf("%ld\t%d\tdied\n", (time - vars->start_time), philo->index + 1);
			pthread_mutex_unlock(&philo->vars->main_mutex);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(500);
	}
	return (NULL);
}

void	routine(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&philo->mutex);
	philo->meal_nbr++;
	printf_text(philo, vars, "is eating");
	philo->time_left_die = get_time() + vars->time_to_die;
	usleep(vars->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
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
	pthread_t	th;

	philo = (t_philo *)arg;
	vars = philo->vars;
	pthread_create(&th, NULL, &watch_hem_die, philo);
	pthread_detach(th);
	pthread_create(&th, NULL, &check_if_finished_eating, arg);
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

	if ((check_arg(ac, av) == 1))
		return (1);
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
		pthread_create(&th, NULL, simulation, &vars->philo[i]);
		i++;
		pthread_detach(th);
		usleep(100);
	}
	pthread_mutex_lock(&vars->main_mutex);
	return (ft_free(vars));
}

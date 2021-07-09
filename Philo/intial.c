/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intial.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:11:39 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/09 15:02:49 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_arg(int ac, char **av)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (ac != 6 && ac != 5)
	{
		printf("check argument\n");
		return (1);
	}
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
			{
				printf("check argument\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	initial_philo(t_vars *vars, int i)
{
	vars->philo[i].vars = vars;
	vars->philo[i].index = i;
	vars->philo[i].right_fork = (i + 1) % vars->nbr_philo;
	vars->philo[i].meal_nbr = 0;
	vars->philo[i].is_full = 0;
}

t_vars	*vars_init(int ac, char **av)
{
	t_vars			*vars;

	if (ac < 6 || ac > 5)
	{
		vars = (t_vars *)malloc(sizeof(t_vars));
		vars->nbr_philo = atoi(av[1]);
		vars->time_to_die = atoi(av[2]);
		vars->time_to_eat = atoi(av[3]);
		vars->time_to_sleep = atoi(av[4]);
		if (ac == 6)
			vars->nbr_must_eat = atoi(av[5]);
		else
			vars->nbr_must_eat = -1;
		vars->philo_finished_eating = 0;
		vars->fork = (pthread_mutex_t *)malloc(
				sizeof(pthread_mutex_t) * vars->nbr_philo);
		vars->philo = (t_philo *)malloc(sizeof(t_philo) * vars->nbr_philo);
		pthread_mutex_init(&vars->mutex_print, NULL);
		pthread_mutex_init(&vars->main_mutex, NULL);
		pthread_mutex_lock(&vars->main_mutex);
		vars->start_time = get_time();
	}
	return (vars);
}

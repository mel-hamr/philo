/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:02:13 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/16 13:29:17 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	printf_text(t_philo *philo, t_vars *vars, char *msg)
{
	long	time;

	time = get_time() - vars->start_time;
	pthread_mutex_lock(&vars->mutex_print);
	printf("%ld\t%d\t%s\n", time, philo->index + 1, msg);
	if (vars->philo_finished_eating == vars->nbr_philo && ft_strlen(msg) == 9)
	{
		printf("simulation over %d\n", philo->index + 1);
		pthread_mutex_unlock(&philo->vars->main_mutex);
		return ;
	}
	pthread_mutex_unlock(&vars->mutex_print);
}

int	ft_free(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->nbr_philo)
	{
		pthread_mutex_destroy(&vars->fork[i]);
		i++;
	}
	free(vars->philo);
	if (vars->fork)
		free(vars->fork);
	pthread_mutex_destroy(&vars->main_mutex);
	pthread_mutex_destroy(&vars->mutex_print);
	free(vars);
	return (0);
}

void	*check_if_finished_eating(void *arg)
{
	t_vars	*vars;
	t_philo	*philo;

	philo = (t_philo *)arg;
	vars = philo->vars;
	while (philo->is_full == 0)
	{
		if (philo->meal_nbr == vars->nbr_must_eat)
		{		
			if (philo->is_full == 0)
			{
				vars->philo_finished_eating++;
				philo->is_full = 1;
			}
		}
		usleep(100);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:02:13 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/06 15:46:17 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_text(t_philo *philo, t_vars *vars, char *msg)
{
	long	time;

	time = get_time() - vars->start_time;
	pthread_mutex_lock(&vars->mutex_print);
	printf("%ld\t%d\t%s\n", time, philo->index + 1, msg);
	pthread_mutex_unlock(&vars->mutex_print);
}

int	ft_free(t_vars *vars)
{
	free(vars->philo);
	free(vars->fork);
	pthread_mutex_destroy(&vars->main_mutex);
	pthread_mutex_destroy(&vars->mutex_print);
	pthread_mutex_destroy(vars->fork);
	free(vars);
	return (0);
}

void	check_if_finished_eating(t_philo *philo, t_vars *vars)
{
	if (philo->is_full == 0)
	{
		vars->philo_finished_eating++;
		philo->is_full = 1;
	}
	if (vars->philo_finished_eating == vars->nbr_philo)
	{
		pthread_mutex_lock(&philo->vars->mutex_print);
		printf("simulation over %d\n", philo->index + 1);
		pthread_mutex_unlock(&philo->vars->main_mutex);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 16:30:57 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/16 16:35:36 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lock_forks(t_philo *philo, t_vars *vars)
{
	sem_wait(vars->forks);
	printf_text(vars, philo, "has taken a fork");
	sem_wait(vars->forks);
	printf_text(vars, philo, "has taken a fork");
}

void	unlock_forks(t_vars *vars)
{
	sem_post(vars->forks);
	sem_post(vars->forks);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:45:57 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/09 13:33:52 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

void	kill_childs(t_vars *var)
{
	int	i;

	i = 0;
	free(var->philo);
	while (i < var->nbr_philo)
	{
		kill(var->pid[i], SIGKILL);
		i++;
	}
	free(var->pid);
	free(var);
	sem_unlink(SEMA_FORK);
	sem_unlink(SEMA_EAT);
	sem_unlink(SEMA_PRINT);
	sem_unlink(SEMA_MAIN);
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
			sem_wait(vars->print_sem);
			printf("%d is dead\n", philo->index);
			sem_post(vars->main_sem);
		}
		if (philo->meal_nbr == vars->nbr_must_eat)
		{
			if (philo->eated++ == 0)
				sem_post(vars->eat_sem);
		}
		usleep(1000);
	}
	return (NULL);
}

void	routine(t_vars *vars, t_philo *philo)
{
	pthread_t	th;

	philo->time_left_die = get_time() + vars->time_to_die;
	pthread_create(&th, NULL, &watch_hem_die, philo);
	pthread_detach(th);
	while (1)
	{
		sem_wait(vars->forks);
		printf_text(vars, philo, "take the first fork");
		sem_wait(vars->forks);
		printf_text(vars, philo, "take the seconde fork");
		philo->time_left_die = get_time() + vars->time_to_die;
		printf_text(vars, philo, "philo is eating");
		usleep(vars->time_to_eat * 1000);
		philo->meal_nbr++;
		sem_post(vars->forks);
		sem_post(vars->forks);
		printf_text(vars, philo, "philo is sleeping");
		usleep(vars->time_to_eat * 1000);
		printf_text(vars, philo, "philo is thinking");
	}
}

void	*check_if_finished(void *arg)
{
	t_vars	*vars;
	int		i;

	i = 0;
	vars = (t_vars *)arg;
	while (i < vars->nbr_philo)
	{
		sem_wait(vars->eat_sem);
		i++;
	}
	sem_wait(vars->print_sem);
	printf("simulation done motherfucker\n");
	sem_post(vars->main_sem);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_vars		*vars;
	int			i;
	int			pid;
	pthread_t	th;

	pid = 1;
	i = -1;
	if ((check_arg(ac, av) == 1))
		return (1);
	vars = (t_vars *)malloc(sizeof(t_vars));
	intial_vars(av, vars, ac);
	while (++i < vars->nbr_philo)
	{
		if (pid != 0)
			pid = intial_process(vars, i);
		else
			break ;
	}
	if (pid == 0)
		routine(vars, &vars->philo[vars->index]);
	pthread_create(&th, NULL, &check_if_finished, (void *)vars);
	sem_wait(vars->main_sem);
	kill_childs(vars);
	return (0);
}

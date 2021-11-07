/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:42:16 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/16 18:25:11 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		sem_wait(philo->sem_philo);
		time = get_time();
		if (time > philo->time_left_die)
		{
			sem_wait(vars->print_sem);
			printf("%ld\t%d\tdied\n", time - vars->start_time, philo->index + 1);
			sem_post(vars->main_sem);
		}
		sem_post(philo->sem_philo);
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
		lock_forks(philo, vars);
		sem_wait(philo->sem_philo);
		philo->time_left_die = get_time() + vars->time_to_die;
		philo->meal_nbr++;
		if (philo->meal_nbr == vars->nbr_must_eat || vars->nbr_must_eat == 0)
		{
			if (philo->eated++ == 0)
				sem_post(vars->eat_sem);
		}
		printf_text(vars, philo, "is eating");
		usleep(vars->time_to_eat * 1000);
		sem_post(philo->sem_philo);
		unlock_forks(vars);
		printf_text(vars, philo, "is sleeping");
		usleep(vars->time_to_eat * 1000);
		printf_text(vars, philo, "is thinking");
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
	printf("simulation done \n");
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

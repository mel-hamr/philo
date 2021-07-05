/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:45:57 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/03 13:23:03 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	printf_text(t_vars *vars, t_philo *philo, char *msg)
{
	long	time;
	long	current_time;

	current_time = get_time();
	time = current_time - vars->start_time;
	sem_wait(vars->print_sem);
	printf("%ld\t%d %s \n", time, philo->index, msg);
	sem_post(vars->print_sem);
}

void	kill_childs(int *pid, int leng)
{
	int	i;

	i = 0;
	while (i < leng)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
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
			sem_wait(vars->print_sem);
			printf("simulation over %d\n", philo->index);
			sem_post(vars->main_sem);
		}
		usleep(100);
	}
	return (NULL);
}

void	routine(int i, int pid, t_vars *vars, t_philo *philo)
{
	int			time;
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

int	main(int ac, char **av)
{
	t_vars	*vars;
	int		i;
	int		pid;

	pid = 1;
	i = 0;	
	if (ac < 6 || ac > 5)
	{
		vars = (t_vars *)malloc(sizeof(t_vars));
		vars->nbr_philo = atoi(av[1]);
		vars->philo = (t_philo *)malloc(sizeof(t_philo) * vars->nbr_philo);
		vars->time_to_die = atoi(av[2]);
		vars->time_to_eat = atoi(av[3]);
		vars->time_to_sleep = atoi(av[4]);
		vars->start_time = get_time();
		if (ac == 6)
			vars->nbr_must_eat = atoi(av[5]);
		else
			vars->nbr_must_eat = -1;
		vars->pid = (int *)malloc(sizeof(int) * vars->nbr_philo);
		sem_unlink(SEMA_MAIN);
		vars->main_sem = sem_open(SEMA_MAIN,O_CREAT,644,1);
		sem_unlink(SEMA_FORK);
		vars->forks = sem_open(SEMA_FORK,O_CREAT,644,vars->nbr_philo);
		sem_unlink(SEMA_PRINT);
		vars->print_sem = sem_open(SEMA_PRINT,O_CREAT,644,1);
	}
	sem_wait(vars->main_sem);
	while (i < vars->nbr_philo)
	{
		if (pid != 0)
		{
			pid = fork();
			vars->pid[i] = pid;
			vars->philo->meal_nbr = 0;
			vars->philo[i].vars = vars;
			vars->index = i;
			vars->philo[i].index = i + 1;
		}
		else
			break;
		i++;
	}
	if (pid == 0)
		routine(i,pid,vars,&vars->philo[vars->index]);
	sem_wait(vars->main_sem);
	kill_childs(vars->pid,vars->nbr_philo);
	return (0);
}

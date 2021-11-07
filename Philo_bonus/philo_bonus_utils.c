/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:45:14 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/12 16:52:08 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	printf("%ld\t%d\t%s \n", time, philo->index, msg);
	sem_post(vars->print_sem);
}

void	intial_vars(char **av, t_vars *vars, int ac)
{
	vars->nbr_philo = ft_atoi(av[1], 0);
	vars->philo = (t_philo *)malloc(sizeof(t_philo) * vars->nbr_philo);
	vars->time_to_die = ft_atoi(av[2], 0);
	vars->time_to_eat = ft_atoi(av[3], 0);
	vars->time_to_sleep = ft_atoi(av[4], 0);
	vars->start_time = get_time();
	vars->philo_finished = 0;
	if (ac == 6)
		vars->nbr_must_eat = atoi(av[5]);
	else
		vars->nbr_must_eat = -1;
	vars->pid = (int *)malloc(sizeof(int) * vars->nbr_philo);
	sem_unlink(SEMA_MAIN);
	vars->main_sem = sem_open(SEMA_MAIN, O_CREAT, 644, 1);
	sem_unlink(SEMA_FORK);
	vars->forks = sem_open(SEMA_FORK, O_CREAT, 644, vars->nbr_philo);
	sem_unlink(SEMA_PRINT);
	vars->print_sem = sem_open(SEMA_PRINT, O_CREAT, 644, 1);
	sem_unlink(SEMA_EAT);
	vars->eat_sem = sem_open(SEMA_EAT, O_CREAT, 644, 0);
	sem_wait(vars->main_sem);
}

int	intial_process(t_vars *vars, int i)
{
	int		pid;
	char	*str;
	char	*tmp;
	char	*str_rest;

	pid = fork();
	vars->pid[i] = pid;
	if (pid == 0)
	{
		str = ft_strdup("SEMA_EAT");
		vars->philo[i].eated = 0;
		vars->philo[i].meal_nbr = 0;
		vars->philo[i].vars = vars;
		vars->philo[i].index = i + 1;
		tmp = str;
		str_rest = ft_itoa(i + 1);
		str = ft_strjoin(str, str_rest);
		free(tmp);
		free(str_rest);
		sem_unlink(str);
		vars->philo[i].sem_philo = sem_open(str, O_CREAT, 644, 1);
		vars->index = i;
	}
	return (pid);
}

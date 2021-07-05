/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:43:07 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/06/16 11:54:54 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str, int *error)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\v') && str[i])
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if ((res * sign) > 2147483647 || (res * sign) < -2147483648)
		*(error) = 1;
	return (res * sign);
}

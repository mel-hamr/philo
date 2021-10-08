/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:21:45 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/07/12 16:24:03 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (s1 == '\0' && s2 == '\0')
		return (NULL);
	j = 0;
	i = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
	{
		str[j] = s1[i];
		j++;
	}
	i = -1;
	while (s2[++i])
	{
		str[j] = s2[i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s;

	i = 0;
	while (s1[i])
		i++;
	s = (char *)malloc(((i + 1) * sizeof(char)));
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

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

static int	ft_count(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = n * (-1);
		count++;
	}
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;
	int		sign;
	long	l;

	l = n;
	sign = 0;
	count = ft_count(l);
	if (l < 0)
	{
		sign = 1;
		l = l * (-1);
	}
	str = (char *)malloc((count + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[count--] = '\0';
	while (count >= 0)
	{
		str[count--] = (l % 10) + '0';
		l = l / 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}

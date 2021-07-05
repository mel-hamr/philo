/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamr <mel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:11:18 by mel-hamr          #+#    #+#             */
/*   Updated: 2021/06/16 11:43:49 by mel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:19:55 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/02 18:23:55 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_digits(int var, char **str)
{
	int	i;
	int	j;

	i = 0;
	while (++i < var)
	{
		j = -1;
		while (str[i][++j] != '\0')
		{
			if ((str[i][j] < '0' || str[i][j] > '9') && \
			str[i][j] != '-' && str[i][j] != '+')
				return (1);
		}
	}
	return (0);
}

int	check_argums(int var, char **str)
{
	if (check_digits(var, str))
		return (error_handler("arguments must only contain digits", 0));
	if (ft_atoi(str[1]) < 1)
		return (error_handler("the number of philos must be higher than 1", 0));
	if (ft_atoi(str[2]) < 0 || ft_atoi(str[3]) < 0 || ft_atoi(str[4]) < 0)
		return (error_handler("times must be positive", 0));
	if (var == 6)
	{
		if (ft_atoi(str[5]) <= 0)
			return (error_handler("if specified, the number of times each philo" \
					" eats during a simulation must be positive", 0));
	}
	return (0);
}

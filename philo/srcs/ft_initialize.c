/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:16:45 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/19 23:43:27 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize(t_times *times, char	**str, int var)
{
	ft_bzero(times, sizeof(t_times));
	times->n_philo = ft_atoi(str[1]);
	times->to_die = ft_atoi(str[2]);
	times->to_eat = ft_atoi(str[3]);
	times->to_sleep = ft_atoi(str[4]);
	if (var == 6)
		times->n_eat = ft_atoi(str[5]);
	else
		times->n_eat = -1;
	gettimeofday(&times->start, NULL);
}

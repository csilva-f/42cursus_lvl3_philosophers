/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_readdata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:20:44 by amenses-          #+#    #+#             */
/*   Updated: 2023/05/17 16:21:15 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkargc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: invalid number of arguments\n");
		return (1);
	}
	return (0);
}

int	valdata(t_data d)
{
	if (d.n_philo < 1 || d.t_die < 0 || d.t_eat < 0 || d.t_sleep < 0)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (d.cap != NULL && *d.cap < 1)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	return (0);
}

t_data	get_data(char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.n_philo = ft_atoi(argv[1]);
	data.t_die = ft_atoi(argv[2]) * 1000;
	data.t_eat = ft_atoi(argv[3]) * 1000;
	data.t_sleep = ft_atoi(argv[4]) * 1000;
	data.end = 0;
	if (argv[5] != NULL)
	{
		data.cap = malloc(sizeof(int));
		*data.cap = ft_atoi(argv[5]);
		data.end = 1 - data.n_philo;
	}	
	if ((data.t_die - data.t_eat - data.t_sleep) / 2 > 0)
		data.t_think = (data.t_die - data.t_eat - data.t_sleep) / 2;
	return (data);
}

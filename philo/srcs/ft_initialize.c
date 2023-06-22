/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:16:45 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/22 23:52:12 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

int	init_vars(t_global *g, char **str, int var)
{
	g->times = malloc(sizeof(t_times));
	g->times->n_philo = ft_atoi(str[1]);
	g->times->to_die = ft_atoi(str[2]);
	g->times->to_eat = ft_atoi(str[3]);
	g->times->to_sleep = ft_atoi(str[4]);
	if (var == 6)
		g->times->n_eat = ft_atoi(str[5]);
	else
		g->times->n_eat = -1;
	gettimeofday(&g->times->start, NULL);
	g->philos = malloc(sizeof(t_philo) * g->times->n_philo);
	if (!g->philos)
	{
		free(g->times);
		return (1);
	}
	return (0);
}

int	free_destroy(t_global *g, int i)
{
	if (i < 0)
	{
		free(g->mtx_forks);
		free(g->philos);
		free(g->times);
	}
	while (i-- >= 0)
	{
		pthread_mutex_destroy(&g->mtx_forks[i]);
		free(g->mtx_forks);
		free(g->philos);
		free(g->times);
	}
	return (1);
}

int	init_mtx_thr(t_global *g)
{
	int	i;

	i = -1;
	g->mtx_forks = malloc(sizeof(pthread_mutex_t) * g->times->n_philo);
	if (!g->mtx_forks)
	{
		free(g->times);
		free(g->philos);
		return (1);
	}
	if (pthread_mutex_init(&g->mtx_print, NULL) || \
			pthread_mutex_init(&g->mtx_death, NULL))
		return (free_destroy(g, i));
	while (++i < g->times->n_philo)
	{
		if (pthread_mutex_init(&g->mtx_forks[i], NULL))
			return (free_destroy(g, i));
	}
	return (0);
}

void	init_philos(t_global *g)
{
	int	i;

	i = 0;
	while (++i <= g->times->n_philo)
	{
		g->philos[i].i = i;
		g->philos[i];
	}
}

int	initialize(t_global *g)
{

	return (0);
}

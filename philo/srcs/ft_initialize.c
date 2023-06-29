/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:16:45 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/28 23:42:32 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_vars(t_global *g, char **str, int var)
{
	g->times = malloc(sizeof(t_times));
	g->times->n_philo = ft_atoi(str[1]);
	g->times->to_die = ft_atoi(str[2]);
	g->times->to_eat = ft_atoi(str[3]);
	g->times->to_sleep = ft_atoi(str[4]);
	g->dead = 0;
	if (var == 6)
		g->times->n_eat = ft_atoi(str[5]);
	else
		g->times->n_eat = -1;
	g->times->start = get_time();
	g->philos = malloc(sizeof(t_philo) * g->times->n_philo);
	if (!g->philos)
	{
		free(g->times);
		return (1);
	}
	return (0);
}

int	free_destroy(t_global *g)
{
	free(g->philos);
	free(g->times);
	return (1);
}

int	init_mtx_thr(t_global *g)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&g->mtx_print, NULL) || \
			pthread_mutex_init(&g->mtx_death, NULL))
		return (free_destroy(g));
	return (0);
}

int	init_forks(t_global *g)
{
	int	i;
	int	j;

	g->times->forks = malloc(sizeof(pthread_mutex_t) * g->times->n_philo);
	if (g->times->forks)
		return (free_destroy(g));
	i = -1;
	while (++i < g->times->n_philo)
	{
		if (pthread_mutex_init(&g->times->forks[i], NULL))
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&g->times->forks[j]);
			free(g->times->forks);
			return (free_destroy(g));
		}
	}
	return (0);
}

int	init_philos(t_global *g)
{
	int		i;

	i = -1;
	while (++i < g->times->n_philo)
	{
		g->philos[i].i = i + 1;
		g->philos[i].n_eat = 0;
		g->philos[i].t_eat = get_time();
		g->philos[i].times = g->times;
	}
	return (0);
}

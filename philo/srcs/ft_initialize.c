/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:16:45 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/26 23:46:47 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <stdlib.h>

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

t_philo	*ft_phnew(int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->i = i;
	philo->n_eat = 0;
	philo->prev = NULL;
	philo->next = NULL;
	return (philo);
}

t_philo	*ft_phlast(t_philo *philo)
{
	if (!philo)
		return (NULL);
	while (philo->next != NULL)
		philo = philo->next;
	return (philo);
}

int	ft_phadd_b(t_philo **philo, t_philo *pnew)
{
	t_philo	*aux;

	if (!pnew)
		return (1);
	if (philo)
	{
		if (*philo)
		{
			aux = ft_phlast(*philo);
			aux->next = pnew;
			pnew->prev = aux;
		}
		else
			*philo = pnew;
	}
	return (0);
}

t_fork	*ft_fnew(int i)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->i_fork = i;
	fork->prev = NULL;
	fork->next = NULL;
	if (pthread_mutex_init(&fork->f_mtx, NULL))
	{
		free(fork);
		return (NULL);
	}
	return (fork);
}

t_fork	*ft_flast(t_fork *forks)
{
	if (!forks)
		return (NULL);
	while (forks->next != NULL)
		forks = forks->next;
	return (forks);
}

int	ft_fadd_b(t_fork **forks, t_fork *fnew)
{
	t_fork	*aux;

	if (!fnew)
		return (1);
	if (forks)
	{
		if (*forks)
		{
			aux = ft_flast(*forks);
			aux->next = fnew;
			fnew->prev = aux;
		}
		else
			*forks = fnew;
	}
	return (0);
}

void	ft_set_forks(t_global *g, int i)
{
	t_fork *aux;

	aux = g->forks;
	while (i > aux->i_fork)
		aux = aux->next;
	g->philos->r_fork = aux;
	g->philos->l_fork = aux->prev;
}

int	init_philos(t_global *g)
{
	int		i;

	i = 0;
	while (++i <= g->times->n_philo)
	{
		if (ft_fadd_b(&g->forks, ft_fnew(i)))
			return (1);
	}
	g->forks->prev = ft_flast(g->forks);
	i = 0;
	while (++i <= g->times->n_philo)
	{
		if (ft_phadd_b(&g->philos, ft_phnew(i)))
			return (1);
		ft_set_forks(g, i);
	}
	return (0);
}

int	initialize(t_global *g)
{
	if (init_mtx_thr(g))
		return (1);
	if (init_philos(g))
		return (1);
	return (0);
}

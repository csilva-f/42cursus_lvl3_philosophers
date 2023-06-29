/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:35:35 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/29 03:05:05 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>

int	print(t_global *g, int i, int action)
{
	u_int64_t	time;

	time = get_time() - g->times->start;
	if (pthread_mutex_lock(&g->mtx_print))
		return (error_handler("failed to lock mutex\n"));
	else
	{
		printf("%" PRId64 " %d ", time, i);
		//checkar se algum ja morreu ou se ja tds comeram o no de vzs max definido
		if (action == DIE)
			printf("died\n");
		else if (action == EAT)
			printf("is eating\n");
		else if (action == FORK)
			printf("has taken a fork\n");
		else if (action == SLEEP)
			printf("is sleeping\n");
		else if (action == THINK)
			printf("is thinking\n");
		if (pthread_mutex_unlock(&g->mtx_print))
			return (error_handler("failed to unlock mutex\n"));
	}
	return (0);
}

void	wait_action(u_int64_t delta_t)
{
	u_int64_t init;

	init = get_time();
	while ((get_time() - init) < delta_t)
		usleep(delta_t * 1000);
}

int	check_death(t_global *g, int n_eat, int i)
{
	int	dead;

	if (pthread_mutex_lock(&g->mtx_death))
		return (error_handler("failed to lock mutex\n"));
	dead = g->dead;
	if (n_eat && i != -1)
	{
		if (g->philos[i].n_eat >= g->times->n_eat)
			dead = 1;
	}
	if (pthread_mutex_lock(&g->mtx_death))
		return (error_handler("failed to unlock mutex\n"));
	return (dead);
}

void	set_death_aux(t_global *g)
{
	int	i;

	i = 0;
	while (i < g->times->n_philo && g->times->n_eat && check_death(g, 1, i))
		i++;
	if (i == g->times->n_philo)
	{
		if (pthread_mutex_lock(&g->mtx_death))
			error_handler("failed to lock mutex\n");
		else
		{
			g->all_eaten = 1;
			if (pthread_mutex_unlock(&g->mtx_death))
				error_handler("failed to unlock mutex\n");
		}
	}
}

void	set_death(t_global *g, int i)
{
	u_int64_t	delta_t;

	while (!g->all_eaten)
	{
		while (++i < g->times->n_philo && !check_death(g, 0, -1))
		{
			if (pthread_mutex_lock(&g->mtx_eat))
				error_handler("failed to lock mutex\n");
			else
			{
				delta_t = get_time() - g->philos[i].t_eat;
				if (delta_t - g->times->to_die >= 0)
				{
					print(g, i, DIE);
					g->dead = 1;
				}
				if (pthread_mutex_unlock(&g->mtx_eat))
					error_handler("failed to unlock mutex\n");
			}
			if (check_death(g, 0, -1))
				break ;
			set_death_aux(g);
		}
	}
}

void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->times->n_philo == 1)
	{

	}
	else if (!(p->i % 2))
		wait_action(p->times->to_eat / 2);
	while (check_death(t_global *g, int n_eat, int i))
	return (NULL);
}

int	create_philo_thrs(t_global *g, int i)
{
	if (pthread_create(&g->philos[i].t, NULL, routine, &g->philos[i]))
	{
		while (i--)
		{
			if (pthread_join(g->philos[i].t, NULL))
				return (error_handler("failed to join threads\n"));
		}
		return (error_handler("failed to create philo's threads\n"));
	}
	return (0);
}

int	simulation_aux(t_global *g)
{
	int	i;

	i = -1;
	while (++i < g->times->n_philo)
	{
		if (pthread_mutex_destroy(&g->times->forks[i]))
			return (error_handler("failed to destroy mutexes\n"));
	}
	if (pthread_mutex_destroy(&g->mtx_death) || pthread_mutex_destroy(&g->mtx_eat) \
			|| pthread_mutex_destroy(&g->mtx_print))
		return (error_handler("failed to destroy mutexes\n"));
	free(g->times->forks);
	free_destroy(g);
	return (0);
}

int	simulation(t_global *g, int i)
{
	while (++i < g->times->n_philo)
	{
		if (create_philo_thrs(g, i))
			return (1);
	}
	set_death(g, -1);
	if (g->times->n_philo == 1)
	{
		if (pthread_detach(g->philos[0].t))
			return (error_handler("failed to detach thread\n"));
	}
	else
	{
		i = -1;
		while (++i < g->times->n_philo)
		{
			if (pthread_join(g->philos[i].t, NULL))
				return (error_handler("failed to join threads\n"));
		}
	}
	return (simulation_aux(g));	
}

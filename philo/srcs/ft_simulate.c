/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:35:35 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/28 00:47:01 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print(t_global *g, t_philo *philo, char *str)
{
	u_int64_t	time;

	time = get_time() - g->times->start;
	pthread_mutex_lock(&g->mtx_print);
	//checkar se algum ja morreu ou se ja todos comeram o numero de vezes maximo definido
	printf("%" PRId64 " %d %s\n", time, philo->i, str);
	pthread_mutex_unlock(&g->mtx_print);
}

void	wait_action(u_int64_t delta_t)
{
	u_int64_t init;

	init = get_time();
	while ((get_time() - init) < delta_t)
		usleep(delta_t * 1000);
}

void	*routine(void *arg)
{
	t_global	*g;

	g = (t_global *)arg;
	if (g->times->n_philo == 1)
	{
		pthread_mutex_lock(&g->philos->r_fork->f_mtx);
		print(g, g->philos, "has taken a fork");
		wait_action(g->times->to_eat);
		pthread_mutex_unlock(&g->philos->r_fork->f_mtx);
	}
	else
	{
		printf("mais philos\n");
	}
}

int	join_threads(t_philo *p, int i)
{
	while (i > 0)
	{
		pthread_join(p->t, NULL);
		i--;
		if (p->prev == NULL)
			break ;
		p = p->prev;
	}
	return (1);
}

int	simulation(t_global *g)
{
	int		i;
	t_philo	*p;

	i = 0;
	p = g->philos;
	while (++i <= g->times->n_philo)
	{
		if (pthread_create(&p->t, NULL, &routine, &g))
			return (join_threads(p, i));
	}
	return (0);;
}

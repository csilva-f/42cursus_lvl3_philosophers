/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:16:45 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/27 23:47:31 by csilva-f         ###   ########.fr       */
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
	if (var == 6)
		g->times->n_eat = ft_atoi(str[5]);
	else
		g->times->n_eat = -1;
	g->times->start = get_time();
	/*g->philos = malloc(sizeof(t_philo) * g->times->n_philo);
	if (!g->philos)
	{
		free(g->times);
		return (1);
	}*/
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

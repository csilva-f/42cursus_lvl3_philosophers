/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:45:57 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/29 00:55:26 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	initialize(t_global *g)
{
	int	i;

	if (init_mtx_thr(g))
		return (error_handler("failed to initialize mutexes"));
	if (init_forks(g))
		return (error_handler("failed to initialize forks"));
	if (init_philos(g))
		return (error_handler("failed to initialize philosophers"));
	i = -1;
	while (++i < g->times->n_philo)
	{
		g->philos[i].r_fork = &g->times->forks[i];
		if (i == 0)
			g->philos[i].l_fork = &g->times->forks[g->times->n_philo - 1];
		else
			g->philos[i].l_fork = &g->times->forks[i - 1];
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:45:57 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/27 23:48:04 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	t_philo	*aux;

	g->forks = NULL;
	g->philos = NULL;
	if (init_mtx_thr(g))
		return (1);
	if (init_philos(g))
		return (1);
	aux = g->philos;
	while (aux->i <= g->times->n_philo)
	{
		aux->t_eat = get_time();
		if (aux->next == NULL)
			break ;
		aux = aux->next;
	}
	return (0);
}

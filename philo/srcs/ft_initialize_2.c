/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:42:03 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/27 23:14:49 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	t_fork	*aux;

	aux = g->forks;
	while (i > aux->i_fork)
		aux = aux->next;
	g->philos->r_fork = aux;
	g->philos->l_fork = aux->prev;
}

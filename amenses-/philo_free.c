/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:13:43 by amenses-          #+#    #+#             */
/*   Updated: 2023/05/17 17:26:33 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	datafree(t_data *d)
{
	if (d->cap != NULL)
		free(d->cap);
	if (d->mtx_offset.mtx != NULL)
		free(d->mtx_offset.mtx);
	if (d->mtx_print.mtx != NULL)
		free(d->mtx_print.mtx);
	if (d->mtx_death.mtx != NULL)
		free(d->mtx_death.mtx);
	if (d->mtx_fcheck.mtx != NULL)
		free(d->mtx_fcheck.mtx);
	if (d->mtx_end.mtx != NULL)
		free(d->mtx_end.mtx);
	return (0);
}

void	forkfree(t_fork *f, int n_philo)
{
	int		i;

	i = 0;
	if (f != NULL)
	{
		while (i++ < n_philo)
		{
			if (f[i - 1].mtx != NULL)
				free(f[i - 1].mtx);
		}
		free(f);
	}
}

void	philofree(t_philo *p, t_fork *f)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = p;
	next = tmp;
	datafree(p->d);
	forkfree(f, p->d->n_philo);
	if (p != NULL)
	{
		while (tmp->next != NULL && tmp->next != p)
		{
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
		free(tmp);
	}
}

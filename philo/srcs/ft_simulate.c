/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:01:39 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/03 23:21:11 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	even_aux(t_info *i)
{
	if (i->state == THINK && get_t() - i->time[1] < i->ttd)
	{
		print(i, PTHINK);
		i->state = NONE;
	}
}

void	*even(void *info)
{
	t_info		*i;

	i = (t_info *)info;
	usleep(1000);
	while (*i->end == 0)
	{
		even_aux(i);
		if (get_t() - i->time[1] > i->ttd && *i->end == 0)
		{
			print(i, PDIED);
			return (0);
		}
		i->state = right_fork(info, i->state, TAKE);
		i->state = left_fork(info, i->state, TAKE);
		if (i->state == BOTH && eat(i, RIGHTHAND) == DIED)
		{
			print(i, PDIED);
			return (0);
		}
		if (i->eaten == i->n_eat)
			return (0);
	}
	return (0);
}

void	odd_aux(t_info *i)
{
	if (i->state == THINK && get_t() - i->time[1] < i->ttd)
	{
		print(i, PTHINK);
		i->state = NONE;
	}
}

void	*odd(void *info)
{
	t_info		*i;

	i = (t_info *)info;
	while (*i->end == 0)
	{
		odd_aux(i);
		if (get_t() - i->time[1] > i->ttd && *i->end == 0)
		{
			print(i, PDIED);
			return (0);
		}
		i->state = left_fork(info, i->state, TAKE);
		i->state = right_fork(info, i->state, TAKE);
		if (i->state == BOTH && eat(i, LEFTHAND) == DIED)
		{
			print(i, PDIED);
			return (0);
		}
		if (i->eaten == i->n_eat)
			return (0);
	}
	return (0);
}

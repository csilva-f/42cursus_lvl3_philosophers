/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:19:41 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/03 23:20:00 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_aux(t_info *i, uint8_t hand)
{
	if (hand == RIGHTHAND)
	{
		i->state = right_fork(i, i->state, DROP);
		i->state = left_fork(i, i->state, DROP);
	}
	else if (hand == LEFTHAND)
	{
		i->state = left_fork(i, i->state, DROP);
		i->state = right_fork(i, i->state, DROP);
	}
}

void	eat_aux2(t_info *i)
{
	if (i->tts <= i->ttd)
	{
		if (i->tts + i->tte > i->ttd)
			usleep((i->ttd - i->tte) * 1000);
		else
			usleep(i->tts * 1000);
	}
	else
	{
		if (i->tte < i->tts)
			usleep((i->tts - i->ttd) * 1000);
		else
			usleep(i->ttd * 1000);
	}
}

uint8_t	eat(t_info *i, uint8_t hand)
{
	i->time[1] = get_t();
	print(i, PEATING);
	i->eaten++;
	usleep(i->tte * 1000);
	if (get_t() - i->time[1] >= i->ttd)
	{
		print(i, PDIED);
		*i->end = 1;
		return (DIED);
	}
	eat_aux(i, hand);
	i->state = THINK;
	if (*i->end == 1)
		return (0);
	print(i, PSLEEP);
	eat_aux2(i);
	if (get_t() - i->time[1] >= i->ttd)
		return (DIED);
	return (ALIVE);
}

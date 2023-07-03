/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:16:45 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/03 01:47:36 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_action(u_int64_t delta_t)
{
	u_int64_t init;

	init = 0;
	init = get_time();
	while ((get_time() - init) < delta_t)
		usleep(delta_t * 1000);
}

void	print(t_info *info, uint32_t type)
{
	pthread_mutex_lock(info->printmutex);
	if (*info->end == 0)
	{
		if (type == PDIED)
		{
			*info->end = 1;
			printf("%llu %d died\n", get_time() - info->time[0], info->id + 1);
		}
		else if (type == PTHINK)
			printf("%llu %d is thinking\n", get_time() - info->time[0], info->id + 1);
		else if (type == PEATING)
			printf("%llu %d is eating\n", get_time() - info->time[0], info->id + 1);
		else if (type == PFORK)
			printf("%llu %d has taken fork\n", get_time() - info->time[0], info->id + 1);
		else if (type == PSLEEP)
			printf("%llu %d is sleeping\n", get_time() - info->time[0], info->id + 1);
	}
	pthread_mutex_unlock(info->printmutex);
}

uint32_t	leftfork(t_info *info, uint32_t state, uint32_t g)
{
	pthread_mutex_lock(info->tforks.l_mtx);
	if (*info->tforks.l_fork == 0 && g == TAKE)
	{
		if (state == RIGHT)
			state = BOTH;
		else if (state == NONE)
			state = LEFT;
		print(info, PFORK);
		*info->tforks.l_fork = 1;
	}
	else if (g == PUTDOWN)
	{
		if (state == BOTH)
			state = RIGHT;
		else if (state == LEFT)
			state = NONE;
		*info->tforks.l_fork = 0;
	}
	pthread_mutex_unlock(info->tforks.l_mtx);
	return (state);
}

uint32_t	rightfork(t_info *info, uint32_t state, uint32_t g)
{
	pthread_mutex_lock(info->tforks.r_mtx);
	if (*info->tforks.r_fork == 0 && g == TAKE)
	{
		if (state == LEFT)
			state = BOTH;
		else if (state == NONE)
			state = RIGHT;
		print(info, PFORK);
		*info->tforks.r_fork = 1;
	}
	else if (g == PUTDOWN)
	{
		if (state == BOTH)
			state = LEFT;
		else if (state == RIGHT)
			state = NONE;
		*info->tforks.r_fork = 0;
	}
	pthread_mutex_unlock(info->tforks.r_mtx);
	return (state);
}

uint8_t	eat(t_info *i, uint8_t hand)
{
	i->time[1] = get_time();
	print(i, PEATING);
	i->buchocheio++;
	usleep(i->tte * 1000);
	if (get_time() - i->time[1] >= i->ttd)
	{
		print(i, PDIED);
		*i->end = 1;
		return (DIED);
	}
	if (hand == RIGHTHAND)
	{
		i->state = rightfork(i, i->state, PUTDOWN);
		i->state = leftfork(i, i->state, PUTDOWN);
	}
	/*else if (hand == LEFTHAND)
	{
		i->state = leftfork(i, i->state, PUTDOWN);
		i->state = rightfork(i, i->state, PUTDOWN);
	}*/
	i->state = THINKING;
	if (*i->end == 1)
		return (0);
	print(i, PSLEEP);
	if (i->tts <= i->ttd)
		usleep(i->tts * 1000);
	else
		usleep(i->ttd * 1000);
	if (get_time() - i->time[1] >= i->ttd)
		return (DIED);
	return (ALIVE);
}

void	*even(void *info)
{
	t_info		*i;

	i = (t_info *)info;
	//wait_action(i->tte / 3);
	while (*i->end == 0)
	{
		if (i->state == THINKING && get_time() - i->time[1] < i->ttd)
		{
			print(i, PTHINK);
			i->state = NONE;
		}
		if (get_time() - i->time[1] > i->ttd && *i->end == 0)
		{
			print(i, PDIED);
			return (0);
		}
		i->state = rightfork(info, i->state, TAKE);
		i->state = leftfork(info, i->state, TAKE);
		if (i->state == BOTH && eat(i, RIGHTHAND) == DIED)
		{
			print(i, PDIED);
			return (0);
		}
		if (i->buchocheio == i->howmanyuntilbuchocheio)
			return (0);
	}
	return (0);
}

void	*odd(void *info)
{
	t_info		*i;

	i = (t_info *)info;
	while (*i->end == 0)
	{
		if (i->state == THINKING && get_time() - i->time[1] < i->ttd)
		{
			print(i, PTHINK);
			i->state = NONE;
		}
		if (get_time() - i->time[1] > i->ttd)
		{
			print(i, PDIED);
			return (0);
		}
		i->state = leftfork(info, i->state, TAKE);
		i->state = rightfork(info, i->state, TAKE);
		//i->state = leftfork(info, i->state, TAKE);
		if (i->state == BOTH && eat(i, LEFTHAND) == DIED)
		{
			print(i, PDIED);
			return (0);
		}
		if (i->buchocheio == i->howmanyuntilbuchocheio)
			return (0);
	}
	return (0);
}

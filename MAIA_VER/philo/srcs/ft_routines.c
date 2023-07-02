/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:39:48 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/02 22:15:14 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_info *info)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&info->end_mtx);
	status = *info->end;
	pthread_mutex_unlock(&info->end_mtx);
	return (status);
}

void	print(t_info *info, uint64_t time, int i, int action)
{
	pthread_mutex_lock(&info->print_mtx);//)
	if (!check_death(info)) //&& death_check_total_eat(philo->rules) != 1)
	{
		if (action == P_DIE)
			printf("%lu %d died\n", time, i);
		else if (action == P_EAT)
			printf("%lu %d is eating\n", time, i);
		else if (action == P_FORK)
			printf("%lu %d has taken a fork\n", time, i);
		else if (action == P_SLEEP)
			printf("%lu %d is sleeping\n", time, i);
		else if (action == P_THINK)
			printf("%lu %d is thinking\n", time, i);
		pthread_mutex_unlock(&info->print_mtx);//)
	}
}

uint32_t	left_fork(t_info *info, uint32_t state, uint32_t g, uint64_t t[])
{
	pthread_mutex_lock(info->tforks.l_mtx);
	if (*info->tforks.l_fork == 0 && g == TAKE && get_time() - info->time[1] <= info->ttd)
	{
		if (state == RIGHT)
			state = BOTH;
		else if (state == NONE)
			state = LEFT;
		print(info, get_time() - t[0], info->id + 1, P_FORK);
		//printf("%lu %d has taken a left fork\n", get_time() - t[0], info->id + 1);
		*info->tforks.l_fork = 1;
	}
	else if (g == DROP && get_time() - info->time[1] <= info->ttd)
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

uint32_t	right_fork(t_info *info, uint32_t state, uint32_t g, uint64_t t[])
{
	pthread_mutex_lock(info->tforks.r_mtx);
	if (*info->tforks.r_fork == 0 && g == TAKE && get_time() - info->time[1] <= info->ttd)
	{
		if (state == LEFT)
			state = BOTH;
		else if (state == NONE)
			state = RIGHT;
		print(info, get_time() - t[0], info->id + 1, P_FORK);
		//printf("%lu %d has taken a right fork\n", get_time() - t[0], info->id + 1);
		*info->tforks.r_fork = 1;
	}
	else if (g == DROP && get_time() - info->time[1] <= info->ttd)
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
	print(i, get_time() - i->time[0], i->id + 1, P_EAT);
	//printf("%lu %d is eating\n", get_time() - i->time[0], i->id + 1);
	i->time[1] = get_time();
	usleep(i->tte * 1000);
	if (hand == RIGHTHAND)
	{
		i->state = right_fork(i, i->state, DROP, i->time);
		i->state = left_fork(i, i->state, DROP, i->time);
	}
	else if (hand == LEFTHAND)
	{
		i->state = left_fork(i, i->state, DROP, i->time);
		i->state = right_fork(i, i->state, DROP, i->time);
	}
	i->state = THINK;
	if (*i->end == 1)
		return (DIED);
	print(i, get_time() - i->time[0], i->id + 1, P_SLEEP);
	//printf("%lu %d is sleeping\n", get_time() - i->time[0], i->id + 1);
	i->time[1] = get_time();
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
	while (!check_death(i))
	{
		if (i->state == THINK && get_time() - i->time[1] < i->ttd && !check_death(i))
		{
			i->time[1] = get_time();
			print(i, get_time() - i->time[0], i->id + 1, P_THINK);
			//printf("%lu %d is thinking\n", get_time() - i->time[0], i->id + 1);
			i->state = NONE;
		}
		if (get_time() - i->time[1] > i->ttd)
		{
			print(i, get_time() - i->time[0], i->id + 1, P_DIE);
			//printf("%lu %d died\n", get_time() - i->time[0], i->id + 1);
			pthread_mutex_lock(&i->end_mtx);
			*i->end = 1;
			pthread_mutex_unlock(&i->end_mtx);
			return (0);
		}
		i->state = right_fork(info, i->state, TAKE, i->time);
		i->state = left_fork(info, i->state, TAKE, i->time);
		if (i->state == BOTH && eat(i, RIGHTHAND) == DIED)
		{
			print(i, get_time() - i->time[0], i->id + 1, P_DIE);
			pthread_mutex_lock(&i->end_mtx);
			*i->end = 1;
			pthread_mutex_unlock(&i->end_mtx);
			//printf("%lu %d died\n", get_time() - i->time[0], i->id + 1);
			return (0);
		}
	}
	return (0);
}

void	*odd(void *info)
{
	t_info		*i;

	i = (t_info *)info;
	while (!check_death(i))
	{
		if (i->state == THINK && get_time() - i->time[1] < i->ttd && !check_death(i))
		{
			i->time[1] = get_time();
			print(i, get_time() - i->time[0], i->id + 1, P_THINK);
			//printf("%lu %d is thinking\n", get_time() - i->time[0], i->id + 1);
			i->state = NONE;
		}
		if (get_time() - i->time[1] > i->ttd)
		{
			print(i, get_time() - i->time[0], i->id + 1, P_DIE);
			//printf("%lu %d died\n", get_time() - i->time[0], i->id + 1);
			pthread_mutex_lock(&i->end_mtx);
			*i->end = 1;
			pthread_mutex_unlock(&i->end_mtx);
			return (0);
		}
		i->state = left_fork(info, i->state, TAKE, i->time);
		i->state = right_fork(info, i->state, TAKE, i->time);
		if (i->state == BOTH && eat(i, LEFTHAND) == DIED)
		{
			print(i, get_time() - i->time[0], i->id + 1, P_DIE);
			pthread_mutex_lock(&i->end_mtx);
			*i->end = 1;
			pthread_mutex_unlock(&i->end_mtx);
			//printf("%lu %d died\n", get_time() - i->time[0], i->id + 1);
			return (0);
		}
	}
	return (0);
}

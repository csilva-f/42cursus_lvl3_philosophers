/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:38:17 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/03 21:43:24 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint32_t	left_fork(t_info *info, uint32_t state, uint32_t g)
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
	else if (g == DROP)
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

uint32_t	right_fork(t_info *info, uint32_t state, uint32_t g)
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
	else if (g == DROP)
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

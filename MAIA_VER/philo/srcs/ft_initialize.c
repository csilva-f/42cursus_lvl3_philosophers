/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:16:45 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/03 01:50:49 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdint.h>

/*void	wait_action(u_int64_t delta_t)
{
	u_int64_t init;

	init = get_time();
	while ((get_time() - init) < delta_t)
		usleep(delta_t * 1000);
}*/

void	init(t_info *info, char **str, pthread_mutex_t *mtx, int argc)
{
	int32_t			i;
	atomic_int		*end;
	pthread_mutex_t	*print_mtx;

	i = -1;
	end = malloc(sizeof(atomic_int *));
	print_mtx = malloc(sizeof(pthread_mutex_t *));
	*end = 0;
	while (++i < ft_atoi(str[1]))
	{
		pthread_mutex_init(&mtx[i], NULL);
		info[i].ttd = ft_atoi(str[2]);
		info[i].tte = ft_atoi(str[3]);
		info[i].tts = ft_atoi(str[4]);
		info[i].n_philos = ft_atoi(str[1]);
		info[i].time[0] = get_time();
		info[i].time[1] = get_time();
		info[i].end = end;
		info[i].printmutex = print_mtx;
		if (argc == 6)
		{
			info[i].howmanyuntilbuchocheio = ft_atoi(str[5]);
			info[i].buchocheio = 0;
		}
		else 
			info[i].howmanyuntilbuchocheio = -1;
	}
}

void	wait_action2(u_int64_t delta_t)
{
	u_int64_t init;

	init = 0;
	init = get_time();
	while ((get_time() - init) < delta_t)
		usleep(delta_t * 1000);
}

void	threads(t_info *info, uint32_t *forks, pthread_t *p_t, pthread_mutex_t *mtx)
{
	int32_t		left;
	uint32_t	i;

	i = -1;
	while (++i < info->n_philos)
	{
		left = i - 1;
		if (i == 0)
			left = info->n_philos - 1;
		forks[i] = 0;
		info[i].id = i;
		info[i].state = THINKING;
		//if ((i + 1) % 2 == 0)
			//info[i].state = NONE;
		info[i].tforks.l_fork = forks + left;
		info[i].tforks.l_mtx = mtx + left;
		info[i].tforks.r_fork = forks + i;
		info[i].tforks.r_mtx = mtx + i;
	}
	i = -1;
	while (++i < info->n_philos)
	{
		if (i % 2 == 0)
		{
			wait_action2(20);//(info->tte / 2);
			pthread_create(&p_t[i], NULL, even, &info[i]);
		}
		else
			pthread_create(&p_t[i], NULL, odd, &info[i]);
	}
}

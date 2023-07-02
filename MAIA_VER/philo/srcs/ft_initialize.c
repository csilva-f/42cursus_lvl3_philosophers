/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:40:27 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/02 21:23:16 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init(t_info *info, char **str, pthread_mutex_t *mtx, int argc)
{
	int32_t			i;
	uint32_t		*end;

	i = -1;
	pthread_mutex_init(&info->end_mtx, NULL);
	pthread_mutex_init(&info->print_mtx, NULL);
	end = malloc(sizeof(uint32_t));
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
		info[i].n_eat_p = 0;
		if (argc == 6)
			info[i].n_eat = ft_atoi(str[5]);
		else
			info[i].n_eat = -1;
	}
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
		info[i].state = THINK;
		if ((i + 1) % 2 == 0)
			info[i].state = NONE;
		info[i].tforks.l_fork = forks + left;
		info[i].tforks.l_mtx = mtx + left;
		info[i].tforks.r_fork = forks + i;
		info[i].tforks.r_mtx = mtx + i;
	}
	i = -1;
	while (++i < info->n_philos)
	{
		if (i % 2 == 0)
			pthread_create(&p_t[i], NULL, even, &info[i]);
		else
			pthread_create(&p_t[i], NULL, odd, &info[i]);
	}
}

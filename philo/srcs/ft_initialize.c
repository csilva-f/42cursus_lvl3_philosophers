/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:41:53 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/03 22:09:06 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_aux(atomic_int **end, pthread_mutex_t **m, atomic_int **start)
{
	*end = malloc(sizeof(atomic_int *));
	*start = malloc(sizeof(atomic_int *));
	*m = malloc(sizeof(pthread_mutex_t *));
	**end = 0;
	**start = 0;
}

void	init_aux2(int argc, t_info **info, int32_t i, char **str)
{
	if (argc == 6)
	{
		(*info)[i].n_eat = ft_atoi(str[5]);
		(*info)[i].eaten = 0;
	}
	else 
		(*info)[i].n_eat = -1;
}

void	init(t_info *info, char **str, pthread_mutex_t *mtx, int argc)
{
	int32_t			i;
	atomic_int		*end;
	pthread_mutex_t	*mprint;
	atomic_int		*start;

	i = -1;
	init_aux(&end, &mprint, &start);
	while (++i < ft_atoi(str[1]))
	{
		pthread_mutex_init(&mtx[i], NULL);
		info[i].ttd = ft_atoi(str[2]);
		info[i].tte = ft_atoi(str[3]);
		info[i].tts = ft_atoi(str[4]);
		info[i].n_philos = ft_atoi(str[1]);
		info[i].time[0] = get_t();
		info[i].time[1] = get_t();
		info[i].end = end;
		info[i].print_mtx = mprint;
		info[i].start = start;
		init_aux2(argc, &info, i, str);
	}
}

void	threads_aux(uint32_t n_philos, int i, int32_t *left)
{
	(*left) = i - 1;
	if (i == 0)
		(*left) = n_philos - 1;
}

void	threads(t_info *info, uint32_t *f, pthread_t *p_t, pthread_mutex_t *mtx)
{
	int32_t		left;
	uint32_t	i;

	i = -1;
	while (++i < info->n_philos)
	{
		threads_aux(info->n_philos, i, &left);
		f[i] = 0;
		info[i].id = i;
		info[i].state = THINK;
		info[i].tforks.l_fork = f + left;
		info[i].tforks.l_mtx = mtx + left;
		info[i].tforks.r_fork = f + i;
		info[i].tforks.r_mtx = mtx + i;
		info[i].c = 0;
	}
	i = -1;
	while (++i < info->n_philos)
	{
		if (i % 2 == 0)
			pthread_create(&p_t[i], NULL, even, &info[i]);
		else
			pthread_create(&p_t[i], NULL, odd, &info[i]);
	}
	*info[0].start = 1;
}

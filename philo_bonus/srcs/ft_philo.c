/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:18:22 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/10 01:01:58 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	init(t_info *info, int argc, char **argv, int *i)
{
	*i = -1;
	info->n_philos = ft_atoi(argv[1]);
	info->pid = malloc(info->n_philos * 4);
	sem_unlink("sem");
	sem_unlink("psem");
	sem_unlink("end");
	info->sem = sem_open("sem", O_CREAT, 0600, info->n_philos);
	info->psem = sem_open("psem", O_CREAT, 0600, 1);
	info->end = sem_open("end", O_CREAT, 0600, 0);
	info->ttd = ft_atoi(argv[2]);
	info->tte = ft_atoi(argv[3]);
	info->tts = ft_atoi(argv[4]);
	info->id = -1;
	info->time[0] = get_t();
	info->eaten = 0;
	if (argc == 6)
		info->n_eat = ft_atoi(argv[5]);
	else 
		info->n_eat = -1;
}

void	*death_check(void *info)
{
	t_info	*i;

	i = (t_info *)info;
	while (1)
	{
		if (get_t() - i->last_eat > i->ttd)
		{
			sem_wait(i->psem);
			printf("%llu %d died\n", get_t() - i->time[0], i->id + 1);
			sem_post(i->end);
		}
		if (i->n_eat == i->eaten)
			sem_post(i->end);
	}
	return (0);
}

void	philo(t_info *i)
{
	pthread_t	t;

	i->last_eat = get_t();
	pthread_create(&t, NULL, death_check, i);
	while (1)
	{
		print(i, THINK);
		sem_wait(i->sem);
		print(i, FORK);
		sem_wait(i->sem);
		print(i, FORK);
		print(i, EAT);
		i->eaten++;
		i->last_eat = get_t();
		usleep(i->tte * 1000);
		sem_post(i->sem);
		sem_post(i->sem);
		print(i, SLEEP);
		usleep(i->tts * 1000);
		usleep(i->ttd - i->tte - i->tts / 2);
	}
}

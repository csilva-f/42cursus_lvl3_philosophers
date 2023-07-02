/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:25:33 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/02 19:29:24 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_info **i, uint32_t **f, pthread_t **p_t, pthread_mutex_t **m)
{
	free((*i)->end);
	free(*i);
	free(*f);
	free(*p_t);
	free(*m);
}

int	main(int argc, char **argv)
{
	t_info			*info;
	int32_t			i;
	uint32_t		*forks;
	pthread_t		*philos_t;
	pthread_mutex_t	*mtx;

	if (argc == 5 || argc == 6)
	{
		info = malloc(ft_atoi(argv[1]) * sizeof(t_info));
		forks = malloc(ft_atoi(argv[1]) * sizeof(uint32_t));
		mtx = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
		philos_t = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
		init(info, argv, mtx, argc);
		threads(info, forks, philos_t, mtx);
		i = -1;
		while (++i < ft_atoi(argv[1]))
			pthread_join(philos_t[i], NULL);
		free_all(&info, &forks, &philos_t, &mtx);
	}
	else
		return (error_handler("wrong number of arguments", 0));
	return (0);
}

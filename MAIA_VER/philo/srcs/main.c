/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:56:39 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/03 01:10:29 by csilva-f         ###   ########.fr       */
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
	pthread_t		*p_threads;
	pthread_mutex_t	*mtx;

	if (argc == 5 || argc == 6)
	{
		if (check_argums(argc, argv))
			return (1);
		info = malloc(ft_atoi(argv[1]) * sizeof(t_info));
		forks = malloc(ft_atoi(argv[1]) * sizeof(uint32_t));
		mtx = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
		p_threads = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
		init(info, argv, mtx, argc);
		threads(info, forks, p_threads, mtx);
		i = -1;
		while (++i < ft_atoi(argv[1]))
			pthread_join(p_threads[i], NULL);
		free_all(&info, &forks, &p_threads, &mtx);
	}
	else
		return (error_handler("invalid number of input parameters", 0));
	return (0);
}

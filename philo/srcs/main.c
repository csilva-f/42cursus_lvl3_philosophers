/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:39:07 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/22 22:55:37 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

u_int64_t	get_time()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (u_int64_t)1000 + tv.tv_usec / 1000));
}

void	ft_1_philo(t_global *g)
{
	printf("0      %d has taken a fork\n", g->times->n_philo);
	usleep(g->times->to_die * 1000);
	printf("%" PRIx64 "    %d died\n", g->times->to_die, g->times->n_philo);
}

int	main(int argc, char **argv)
{
	t_global	g;

	if (argc == 5 || argc == 6)
	{
		if (check_argums(argc, argv))
			return (1);
		if (init_vars(&g, argv, argc))
			return (1);
		if (g.times->n_philo == 1)
		{
			ft_1_philo(&g);
			return (0);
		}
		else
			printf("More than 1 philo\n");
	}
	else
		printf("Error: wrong number of arguments\n");
	return (0);
}

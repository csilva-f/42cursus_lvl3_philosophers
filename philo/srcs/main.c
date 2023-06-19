/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:39:07 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/19 23:45:14 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_1_philo(t_times *times)
{
	printf("0 %d has taken a fork\n", times->n_philo);
	usleep(times->to_die * 1000);
	printf("%u %d died\n", times->to_die, times->n_philo);
}

int	main(int argc, char **argv)
{
	t_times	times;

	if (argc == 5 || argc == 6)
	{
		if (check_argums(argc, argv))
			return (1);
		initialize(&times, argv, argc);
		printf("n_philo2: %d\n", times.n_philo);
		if (times.n_philo == 1)
		{
			ft_1_philo(&times);
			return (0);
		}
		else
			printf("More than 1 philo\n");
	}
	else
		printf("Error: wrong number of arguments\n");
	return (0);
}

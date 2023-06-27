/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:39:07 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/27 23:46:19 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_global *g)
{
	int 	i;
	t_fork	*aux_f;
	t_philo	*aux_p;

	i = 0;
	while (++i <= g->times->n_philo)
	{
		aux_f = g->forks->next;
		free(g->forks);
		aux_p = g->philos->next;
		free(g->philos);
		g->forks = aux_f;
		g->philos = aux_p;
	}
	free(g->times);
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
		if (initialize(&g))
			return (1);
		free_all(&g);	
	}
	else
		printf("Error: wrong number of arguments\n");
	return (0);
}

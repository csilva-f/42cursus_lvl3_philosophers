/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:39:07 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/29 00:58:33 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_global *g)
{
	free(g->times->forks);
	free(g->philos);
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
			return (error_handler("failed to initialize all variables"));
		if (initialize(&g))
			return (1);
		if (simulation(&g))
			return (1);
		free_all(&g);	
	}
	else
		return(error_handler("wrong number of arguments"));
	return (0);
}

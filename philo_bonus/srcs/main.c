/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:18:22 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/10 01:07:03 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	fork_id_aux(t_info *info, int i, uint32_t *fork_id)
{
	*fork_id = fork();
	if (*fork_id != 0)
		info->pid[i] = *fork_id;
}

int	main(int argc, char **argv)
{
	t_info		info;
	int32_t		i;
	uint32_t	fork_id;

	if (argc == 5 || argc == 6)
	{
		fork_id = -1;
		init(&info, argc, argv, &i);
		while (++i < info.n_philos && fork_id != 0)
			fork_id_aux(&info, i, &fork_id);
		info.id = i - 1;
		if (fork_id == 0)
			philo(&info);
		else
		{
			sem_wait(info.end);
			i = -1;
			while (++i < info.n_philos)
				kill(info.pid[i], SIGTERM);
			waitpid(-1, NULL, 0);
		}
	}
	else
		return (error_handler("invalid number of arguments", 0));
}

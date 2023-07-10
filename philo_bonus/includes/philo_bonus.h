/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 21:11:24 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/10 01:03:13 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define THINK 1
# define EAT 2
# define SLEEP 3
# define FORK 4

# include <errno.h>
# include <signal.h>
# include <stdatomic.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_info
{
	int32_t				n_philos;
	uint64_t			ttd;
	uint64_t			tte;
	uint64_t			tts;
	uint64_t			time[2];
	uint32_t			state;
	uint32_t			id;
	uint32_t			*pid;
	_Atomic uint64_t	last_eat;
	uint32_t			philos;
	sem_t				*psem;
	sem_t				*end;
	sem_t				*sem;
	int					n_eat;
	atomic_int			eaten;
}	t_info;

//------------------------------------------- UTILS -------------------------------------------
long int	ft_atoi(const char *nptr);
uint64_t	get_t(void);
void		print(t_info *i, int type);
int			error_handler(char *str, int i);

//------------------------------------------- PHILO -------------------------------------------
void		init(t_info *info, int argc, char **argv, int *i);
void		*death_check(void *info);
void		philo(t_info *i);

#endif

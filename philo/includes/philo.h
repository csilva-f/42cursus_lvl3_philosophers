/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:39:39 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/22 23:26:09 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bits/types/struct_timeval.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <inttypes.h>

typedef struct s_times
{
	int				n_philo;
	u_int64_t		to_die;
	u_int64_t		to_eat;
	u_int64_t		to_sleep;
	int				n_eat;
	struct timeval	start;
}			t_times;

typedef struct	s_fork
{
	int				i_fork;
	pthread_mutex_t	*mtx;
}			t_fork;

typedef struct	s_philo
{
	int			i;
	pthread_t	t;
}			t_philo;

typedef struct	s_global
{
	t_times			*times;
	t_philo			*philos;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_death;
}			t_global;

//----------------------------------SRCS------------------------------------
//CHECK
int				check_digits(int var, char **str);
int				check_argums(int var, char **str);

//INITIALIZE
int				init_vars(t_global *g, char **str, int var);

//UTILS
void			*ft_bzero(void *s, size_t n);
long int		ft_atoi(const char *nptr);

#endif

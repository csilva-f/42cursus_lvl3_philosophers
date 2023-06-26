/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:39:39 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/26 23:47:23 by csilva-f         ###   ########.fr       */
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
	pthread_mutex_t	f_mtx;
	struct s_fork	*prev;
	struct s_fork	*next;
}			t_fork;

typedef struct	s_philo
{
	int				i;
	pthread_t		t;
	int				n_eat;
	t_fork			*l_fork;
	t_fork			*r_fork;
	struct s_philo	*prev;
	struct s_philo	*next;
}			t_philo;

typedef struct	s_global
{
	t_times			*times;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_death;
}			t_global;

//----------------------------------SRCS------------------------------------
//CHECK
int				check_digits(int var, char **str);
int				check_argums(int var, char **str);

//INITIALIZE
int				init_vars(t_global *g, char **str, int var);
int				initialize(t_global *g);

//UTILS
void			*ft_bzero(void *s, size_t n);
long int		ft_atoi(const char *nptr);

#endif

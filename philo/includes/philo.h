/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:39:39 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/29 03:04:33 by csilva-f         ###   ########.fr       */
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

# define DIE 0
# define EAT 1
# define FORK 2
# define SLEEP 3
# define THINK 4

typedef struct s_times
{
	int				n_philo;
	u_int64_t		to_die;
	u_int64_t		to_eat;
	u_int64_t		to_sleep;
	int				n_eat;
	u_int64_t		start;
	pthread_mutex_t	*forks;
}			t_times;

typedef struct	s_philo
{
	int				i;
	pthread_t		t;
	int				n_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	u_int64_t		t_eat;
	t_times			*times;
}			t_philo;

typedef struct	s_global
{
	t_times			*times;
	t_philo			*philos;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_death;
	pthread_mutex_t	mtx_eat;
	int				dead;
	int				all_eaten;
}			t_global;

//----------------------------------SRCS------------------------------------
//CHECK
int				check_digits(int var, char **str);
int				check_argums(int var, char **str);

//INITIALIZE
int				init_vars(t_global *g, char **str, int var);
int				free_destroy(t_global *g);
int				init_mtx_thr(t_global *g);
int				init_forks(t_global *g);
int				init_philos(t_global *g);

//INITIALIZE 2
int				initialize(t_global *g);

//SIMULATE
int				print(t_global *g, int i, int action);
void			wait_action(u_int64_t delta_t);
void			*routine(void *global);
int				join_threads(t_philo *p, int i);
int				simulation(t_global *g, int i);

//UTILS
void			*ft_bzero(void *s, size_t n);
long int		ft_atoi(const char *nptr);
u_int64_t		get_time(void);
int				error_handler(char *str);

#endif

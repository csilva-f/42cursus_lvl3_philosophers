/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:39:39 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/27 23:46:44 by csilva-f         ###   ########.fr       */
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
	u_int64_t		start;
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
	u_int64_t		t_eat;
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
int				free_destroy(t_global *g);
int				init_mtx_thr(t_global *g);
t_philo			*ft_phnew(int i);
t_philo			*ft_phlast(t_philo *philo);

//INITIALIZE 2
int				ft_phadd_b(t_philo **philo, t_philo *pnew);
t_fork			*ft_fnew(int i);
t_fork			*ft_flast(t_fork *forks);
int				ft_fadd_b(t_fork **forks, t_fork *fnew);
void			ft_set_forks(t_global *g, int i);

//INITIALIZE 3
int				init_philos(t_global *g);
int				initialize(t_global *g);

//UTILS
void			*ft_bzero(void *s, size_t n);
long int		ft_atoi(const char *nptr);
u_int64_t		get_time(void);

#endif

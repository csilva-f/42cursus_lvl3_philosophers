/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 10:31:49 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/03 01:45:41 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdatomic.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define BOTH 3
# define LEFT 2
# define RIGHT 1
# define NONE 0
# define THINKING 4
# define PUTDOWN 0
# define TAKE 1
# define LEFTHAND 0
# define RIGHTHAND 1
# define DIED 1
# define ALIVE 0

# define PDIED 0
# define PSLEEP 1
# define PEATING 2
# define PTHINK 3
# define PFORK 4

typedef struct s_forks{
	uint32_t		*l_fork;
	uint32_t		*r_fork;
	pthread_mutex_t	*l_mtx;
	pthread_mutex_t	*r_mtx;
}		t_forks;

typedef struct s_info{
	t_forks			tforks;
	uint32_t		n_philos;
	uint32_t		id;
	uint32_t		ttd;
	uint32_t		tte;
	uint32_t		tts;
	uint32_t		state;
	uint64_t		time[2];
	atomic_int		*end;
	int32_t		buchocheio;
	int32_t		howmanyuntilbuchocheio;
	pthread_mutex_t	*printmutex;
}		t_info;

//-----------------------------------SRCS-----------------------------------
//CHECK
int					check_digits(int var, char **str);
int					check_argums(int var, char **str);

//INITIALIZE
void				wait_action(u_int64_t delta_t);
void				init(t_info *info, char **str, pthread_mutex_t *mtx, int argc);
//void				threads_aux(t_info **info, uint32_t **f, pthread_mutex_t *mtx);
void				threads(t_info *info, uint32_t *f, pthread_t *p_t, pthread_mutex_t *mtx);

//ROUTINES
uint32_t			left_fork(t_info *info, uint32_t i_state, uint32_t f_state, uint64_t t[]);
uint32_t			right_fork(t_info *info, uint32_t i_state, uint32_t f_state, uint64_t t[]);
uint8_t				eat(t_info *i, uint8_t hand);
void				*even(void *info);
void				*odd(void *info);

//UTILS
long int			ft_atoi(const char *nptr);
u_int64_t			get_time(void);
int					error_handler(char *str, int f);

#endif

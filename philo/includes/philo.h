/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:39:39 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/19 23:27:01 by csilva-f         ###   ########.fr       */
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

typedef struct s_times
{
	int				n_philo;
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	int				n_eat;
	struct timeval	start;
}			t_times;

//----------------------------------SRCS------------------------------------
//CHECK
int				check_digits(int var, char **str);
int				check_argums(int var, char **str);

//INITIALIZE
void			initialize(t_times *times, char	**str, int var);

//UTILS
void			*ft_bzero(void *s, size_t n);
long int		ft_atoi(const char *nptr);

#endif

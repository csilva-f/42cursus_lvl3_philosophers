/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:18:22 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/03 20:02:58 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	ft_atoi(const char *nptr)
{
	int			i;
	int			c;
	long int	res;
	int			n;

	i = 0;
	c = 1;
	res = 0;
	n = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while ((nptr[i] == '+' || nptr[i] == '-') && c == 1 && n == 0)
	{
		if (nptr[i] == '-')
			c = -1;
		i++;
		n++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * c);
}

u_int64_t	get_t(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (u_int64_t)1000 + tv.tv_usec / 1000));
}

void	print(t_info *i, uint32_t type)
{
	pthread_mutex_lock(i->print_mtx);
	if (*i->end == 0)
	{
		if (type == PDIED && *i->end == 0)
		{
			*i->end = 1;
			printf("%lu %d died\n", get_t() - i->time[0], i->id + 1);
		}
		else if (type == PTHINK)
			printf("%lu %d is thinking\n", get_t() - i->time[0], i->id + 1);
		else if (type == PEATING)
			printf("%lu %d is eating\n", get_t() - i->time[0], i->id + 1);
		else if (type == PFORK)
			printf("%lu %d has taken a fork\n", get_t() - i->time[0], i->id + 1);
		else if (type == PSLEEP)
			printf("%lu %d is sleeping\n", get_t() - i->time[0], i->id + 1);
	}
	pthread_mutex_unlock(i->print_mtx);
}

int	error_handler(char *str, int i)
{
	printf("Error: %s\n", str);
	if (i == 1)
		return (-1);
	return (1);
}

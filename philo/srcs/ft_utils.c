/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:09:07 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/19 23:13:11 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*str2;
	int				i;

	str2 = s;
	i = 0;
	while (n > 0)
	{
		str2[i] = 0;
		i++;
		n--;
	}
	return (s);
}

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

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (u_int64_t)1000 + tv.tv_usec / 1000));
}

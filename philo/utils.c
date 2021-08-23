/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraphael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:54:07 by fraphael          #+#    #+#             */
/*   Updated: 2021/08/05 13:54:10 by fraphael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	if (str)
		printf("%s%s%s\n", KRED, str, KNRM);
	return (0);
}

long	get_time(void)
{
	struct timeval	time;
	long			time_mill;

	gettimeofday(&time, NULL);
	time_mill = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return (time_mill);
}

void	my_usleep(int time)
{
	long	res;

	res = get_time() + time;
	while (get_time() < res)
	{
		usleep(50);
	}
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned long	r;

	r = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
	}
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (r > LONG_MAX && (sign == 1))
			return (-1);
		if (r > LONG_MAX && (sign == -1))
			return (0);
		r = r * 10 + *str - '0';
		str++;
	}
	return (sign * (int)r);
}

void	free_all(t_simulation *sim, t_philo *philo, pthread_mutex_t *forks)
{
	if (philo)
		free(philo);
	if (forks)
		free(forks);
	if (sim)
		free(sim);
}

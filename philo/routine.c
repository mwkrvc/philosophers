/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraphael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:54:16 by fraphael          #+#    #+#             */
/*   Updated: 2021/08/05 13:54:17 by fraphael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *ph)
{
	if (ph->type == LEFTY && ph->state != DEAD)
	{
		pthread_mutex_lock(&ph->sim->forks[ph->id - 1]);
		pthread_mutex_lock(&ph->sim->print_state);
		printf("%lu %d has taken a fork\n", get_time() - ph->sim->start, ph->id);
		pthread_mutex_unlock(&ph->sim->print_state);
		pthread_mutex_lock(&ph->sim->forks[ph->id % ph->sim->num]);
		pthread_mutex_lock(&ph->sim->print_state);
		printf("%lu %d has taken a fork\n", get_time() - ph->sim->start, ph->id);
		pthread_mutex_unlock(&ph->sim->print_state);
	}
	else if (ph->type == RIGHTY && ph->state != DEAD)
	{
		pthread_mutex_lock(&ph->sim->forks[ph->id % ph->sim->num]);
		pthread_mutex_lock(&ph->sim->print_state);
		printf("%lu %d has taken a fork\n", get_time() - ph->sim->start, ph->id);
		pthread_mutex_unlock(&ph->sim->print_state);
		pthread_mutex_lock(&ph->sim->forks[ph->id - 1]);
		pthread_mutex_lock(&ph->sim->print_state);
		printf("%lu %d has taken a fork\n",
			   get_time() - ph->sim->start, ph->id);
		pthread_mutex_unlock(&ph->sim->print_state);
	}
}

void	eat(t_philo *philo)
{
	if (philo->state != DEAD)
	{
		philo->eat_count--;
		pthread_mutex_lock(&philo->dead);
		philo->time_to_die = get_time() + philo->sim->time_to_die;
		pthread_mutex_unlock(&philo->dead);
		philo->state = EATING;
		printf("%lu %d is eating\n",
			   get_time() - philo->sim->start, philo->id);
		my_usleep(philo->sim->time_to_eat);
	}
}

void	forks_down(t_philo *philo)
{
	if (philo->type == LEFTY && philo->state != DEAD)
	{
		pthread_mutex_unlock(&philo->sim->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->sim->forks[philo->id % philo->sim->num]);
	}
	else if (philo->type == RIGHTY && philo->state != DEAD)
	{
		pthread_mutex_unlock(&philo->sim->forks[philo->id % philo->sim->num]);
		pthread_mutex_unlock(&philo->sim->forks[philo->id - 1]);
	}
	if (philo->state != DEAD)
	{
		pthread_mutex_lock(&philo->sim->print_state);
		printf("%lu %d is sleeping\n",
			   get_time() - philo->sim->start, philo->id);
		pthread_mutex_unlock(&philo->sim->print_state);
		philo->state = SLEEPING;
		my_usleep(philo->sim->time_to_sleep);
		pthread_mutex_lock(&philo->sim->print_state);
		printf("%lu %d is thinking\n",
			   get_time() - philo->sim->start, philo->id);
		pthread_mutex_unlock(&philo->sim->print_state);
		philo->state = THINKING;
	}
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (philo->state != DEAD)
	{
		take_forks(philo);
		eat(philo);
		forks_down(philo);
	}
	return (NULL);
}

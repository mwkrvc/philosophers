/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraphael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:54:24 by fraphael          #+#    #+#             */
/*   Updated: 2021/08/05 13:54:25 by fraphael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	assign_starting_params(t_simulation *sim, char **argv, int argc)
{
	sim->num = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (!((sim->num > 0 && sim->num <= 200) && sim->time_to_die >= 60
			&& sim->time_to_eat >= 60 && sim->time_to_sleep >= 60))
		return (0);
	if (argc == 6)
	{
		sim->eat_count = ft_atoi(argv[5]);
		if (sim->eat_count <= 0)
			return (0);
	}
	else
		sim->eat_count = INT_MIN;
	return (1);
}

void	init_philo(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num)
	{
		sim->philo[i].sim = sim;
		sim->philo[i].id = i + 1;
		sim->philo[i].eat_count = sim->eat_count;
		sim->philo[i].time_to_die = sim->time_to_die + get_time();
		if (sim->philo[i].id % 2)
			sim->philo[i].type = RIGHTY;
		else
			sim->philo[i].type = LEFTY;
		i++;
	}
}

void	clear_inits(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num)
	{
		pthread_mutex_destroy(&sim->philo[i].dead);
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->print_state);
}

int	init_sim(t_simulation *sim)
{
	int	i;

	sim->philo = (t_philo *) malloc(sizeof(*(sim->philo)) * (sim->num + 1));
	if (!sim->philo)
		return (error("Malloc error"));
	sim->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * sim->num);
	if (!sim->forks)
		return (error("Malloc error"));
	i = 0;
	while (i < sim->num)
	{
		pthread_mutex_init(&(sim->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&sim->print_state, NULL);
	init_philo(sim);
	threads(sim);
	clear_inits(sim);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraphael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:53:55 by fraphael          #+#    #+#             */
/*   Updated: 2021/08/05 17:07:51 by fraphael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_simulation(t_simulation *sim)
{
	int	stop;
	int	i;

	i = 0;
	stop = 0;
	while (i < sim->num)
	{
		if (sim->philo[i].eat_count <= 0 && sim->philo[i].eat_count != INT_MIN)
		{
			stop++;
		}
		if (stop == sim->num)
			return (1);
		pthread_mutex_lock(&sim->philo[i].dead);
		if (sim->philo[i].time_to_die < get_time())
		{
			pthread_mutex_lock(&sim->print_state);
			printf("%s%lu %d is dead%s\n", KRED,
				   get_time() - sim->start, sim->philo[i].id, KNRM);
			return (1);
		}
		pthread_mutex_unlock(&sim->philo[i].dead);
		i++;
	}
	return (0);
}

void	threads(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->philo[i].sim->start = get_time();
	while (i < sim->num)
	{
		pthread_mutex_init(&sim->philo[i].dead, NULL);
		pthread_create(&(sim->philo[i].tid), NULL,
			   &routine, (void *)(&sim->philo[i]));
		i++;
	}
	i = 0;
	while (i < sim->num)
	{
		pthread_detach(sim->philo[i].tid);
		i++;
	}
	while (1)
	{
		if (stop_simulation(sim))
			return ;
	}
}

int	setup_simulation(int argc, char **argv, t_simulation *sim)
{
	if (!(argc == 5 || argc == 6))
		return (error("Invalid number of arguments"));
	if (!assign_starting_params(sim, argv, argc))
		return (error("Invalid argument"));
	if (!init_sim(sim))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	*sim;

	sim = (t_simulation *) malloc(sizeof (t_simulation));
	if (!setup_simulation(argc, argv, sim))
	{
		free_all(sim, NULL, NULL);
		return (-1);
	}
	free_all(sim, sim->philo, sim->forks);
	return (0);
}

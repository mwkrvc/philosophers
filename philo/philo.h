/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraphael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:59:46 by fraphael          #+#    #+#             */
/*   Updated: 2021/08/05 13:59:51 by fraphael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KBLU  "\x1B[34m"

# define EATING 1
# define THINKING 2
# define SLEEPING 3
# define DEAD 5

# define LEFTY 1
# define RIGHTY 2

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

struct	s_simulation;

typedef struct s_philo
{
	int					state;
	int					id;
	int					type;
	int					eat_count;
	long				time_to_die;
	pthread_t			tid;
	pthread_mutex_t		dead;
	struct s_simulation	*sim;
}	t_philo;

typedef struct s_simulation
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_state;
	t_philo			*philo;
}	t_simulation;

// ROUTINE
void	threads(t_simulation *sim);
void	*routine(void *philosopher);

// UTILS
void	my_usleep(int time);
long	get_time(void);
int		error(char *str);
int		ft_atoi(const char *str);
void	free_all(t_simulation *sim, t_philo *philo, pthread_mutex_t *forks);

// SETUP
int		init_sim(t_simulation *sim);
int		assign_starting_params(t_simulation *sim, char **argv, int argc);

#endif

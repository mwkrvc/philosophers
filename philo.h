#ifndef PHILO_H
#define PHILO_H

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define EAT 0
#define THINK 1
#define SLEEP 2
#define DEAD 3

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_philo
{
    int is_eating;
    int last_ate;
}               t_philo;


typedef struct s_simulation
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_count;
    t_philo *philo;
}               t_simulation;

// LIB FUNCTIONS
int ft_strlen(const char *str);
int	ft_atoi(const char *str);

#endif

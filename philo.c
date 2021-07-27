
#include "philo.h"

int error(char *str)
{
    if (str)
        printf("%s%s%s\n", KRED, str, KNRM);
    return (0);
}

void init_philo(t_simulation *sim)
{
    int i;

    i = 0;
    while (i < sim->number_of_philosophers)
    {
        sim->philo[i].is_eating = 0;
        sim->philo[i].last_ate = 0;
        i++;
    }
}

int init_sim(int argc, char **argv, t_simulation *sim)
{
    sim->number_of_philosophers = ft_atoi(argv[1]);
    sim->time_to_die = ft_atoi(argv[2]);
    sim->time_to_eat = ft_atoi(argv[3]);
    sim->time_to_sleep = ft_atoi(argv[4]);
    if (!(sim->number_of_philosophers > 0 && sim->time_to_die > 0
          && sim->time_to_eat > 0 && sim->time_to_sleep > 0))
        return (error("Invalid argument"));
    if (argc == 6)
    {
        sim->eat_count = ft_atoi(argv[5]);
        if (sim->eat_count <= 0)
            return (error("Invalid argument"));
    }
    else
        sim->eat_count = 0;
    sim->philo = (t_philo *) malloc(sizeof(*(sim->philo)) * sim->number_of_philosophers);
    if (!(sim->philo))
        return (error("Malloc error"));
    init_philo(sim);
    return (1);
}

int setup_simulation(int argc, char **argv, t_simulation *sim)
{
    if (!(argc == 5 || argc == 6))
        return (error("Invalid number of arguments"));
    if (!init_sim(argc, argv, sim))
        return (0);
    return (1);
}

//void cycle()
//{
//    while (1)
//    {
////         grab forks
////         eat
////         put down forks
////         sleep ?? think ?? idk
//    }
//}

int main(int argc, char **argv)
{
    t_simulation   *sim;

    sim = (t_simulation*) malloc(sizeof (t_simulation));
    if (!setup_simulation(argc, argv, sim))
        return (-1);
    return 0;
}

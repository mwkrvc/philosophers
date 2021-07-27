
#include "philo.h"

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
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
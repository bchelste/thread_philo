/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:26:22 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/06 13:52:20 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int		res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == 'v')
		|| (str[i] == 'r') || (str[i] == '\f') || (str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

long	ft_time(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return (te.tv_sec * 1000 + te.tv_usec / 1000);
}

void	ft_usleep(int interval)
{
	long	sleep;

	sleep = ft_time() + interval;
	while (ft_time() < sleep)
		usleep(interval);
}

void	ft_output(t_philo *philo)
{
	long	output_time;

	output_time = ft_time() - philo->init_time;
	sem_wait(philo->output);
	if (philo->state == 8)
		printf("%ld ms %d has taken a left  fork\n", output_time, philo->nbr);
	if (philo->state == 9)
		printf("%ld ms %d has taken a right fork\n", output_time, philo->nbr);
	if (philo->state == 1)
		printf("%ld ms %d philo is eating\n", output_time, philo->nbr);
	if (philo->state == 2)
		printf("%ld ms %d philo is sleeping\n", output_time, philo->nbr);
	if (philo->state == 3)
		printf("%ld ms %d philo is thinking\n", output_time, philo->nbr);
	sem_post(philo->output);
}

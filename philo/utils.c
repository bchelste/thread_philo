/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 12:09:11 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/03 02:22:48 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_output(t_philo *philo)
{
	long	output_time;

	output_time = ft_time() - philo->init_time;
	pthread_mutex_lock(philo->output);
	if (philo->state == 8)
		printf("%ld ms %d has taken a left  fork %d\n",
			output_time, philo->nbr, philo->l_fork->id);
	if (philo->state == 9)
		printf("%ld ms %d has taken a right fork %d\n",
			output_time, philo->nbr, philo->r_fork->id);
	if (philo->state == 1)
		printf("%ld ms %d philo is eating\n", output_time, philo->nbr);
	if (philo->state == 2)
		printf("%ld ms %d philo is sleeping\n", output_time, philo->nbr);
	if (philo->state == 3)
		printf("%ld ms %d philo is thinking\n", output_time, philo->nbr);
	pthread_mutex_unlock(philo->output);
}

void	ft_usleep(int interval)
{
	long	sleep;

	sleep = ft_time() + interval;
	while (ft_time() < sleep)
		usleep(interval);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 16:21:11 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/05 15:41:29 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_death(t_data *data, int i)
{
	long		tm;

	if ((ft_time() - data->philos[i].tm_aft_meal) > data->time_to_die)
	{
		pthread_mutex_lock(&data->output);
		data->dead = 1;
		tm = ft_time() - data->philos[i].init_time;
		printf("%ld ms %d philo is dead\n", tm, data->philos[i].nbr);
		return (1);
	}
	return (0);
}

void	ft_checker(t_data *data)
{
	int			i;
	int			tmp;

	while (1)
	{
		i = 0;
		tmp = 0;
		while (i < data->nbr_of_philo)
		{
			if (ft_death(data, i) == 1)
				return ;
			if (data->philos[i].nbr_cycle == data->nbr_of_eat)
				tmp++;
			i++;
		}
		if (tmp == data->nbr_of_philo)
		{
			pthread_mutex_lock(&data->output);
			printf("everybody has eaten the required number of times\n");
			return ;
		}
	}
}

static void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->fork);
	philo->l_fork->lock = 1;
	philo->state = 8;
	ft_output(philo);
	pthread_mutex_lock(&philo->r_fork->fork);
	philo->r_fork->lock = 1;
	philo->state = 9;
	ft_output(philo);
	pthread_mutex_unlock(philo->wait);
	philo->tm_aft_meal = ft_time();
	philo->state = 1;
	ft_output(philo);
	ft_usleep(philo->time_to_eat);
	if (philo->nbr_of_eat != -1)
		philo->nbr_cycle++;
	pthread_mutex_unlock(&philo->l_fork->fork);
	philo->l_fork->lock = 0;
	pthread_mutex_unlock(&philo->r_fork->fork);
	philo->r_fork->lock = 0;
}

static void	ft_action(t_philo *philo)
{
	pthread_mutex_lock(philo->wait);
	if ((philo->l_fork->lock == 0) && (philo->r_fork->lock == 0))
	{
		ft_eating(philo);
		if (philo->nbr_cycle == philo->nbr_of_eat)
			return ;
		philo->state = 2;
		ft_output(philo);
		ft_usleep(philo->time_to_sleep);
		philo->state = 3;
		ft_output(philo);
	}
	else
		pthread_mutex_unlock(philo->wait);
}

void	*ft_philo(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (philo->nbr_cycle != philo->nbr_of_eat)
	{
		if (*(philo->dead) == 1)
			return (NULL);
		ft_action(philo);
	}
	return (NULL);
}

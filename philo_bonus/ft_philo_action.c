/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:26:45 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/06 13:57:04 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_check_meal(void *ptr)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)ptr;
	while (i < data->nbr_of_philo)
	{
		sem_wait(data->counter);
		if (data->break_thread == 1)
			return (NULL);
		i++;
	}
	sem_wait(data->output);
	printf("everybody has eaten the required number of times\n");
	sem_post(data->death);
	return (NULL);
}

static void	*ft_check(void *ptr)
{
	t_philo	*philo;
	long	tm;

	philo = (t_philo *)ptr;
	while (1)
	{
		if ((ft_time() - philo->tm_aft_meal) > philo->time_to_die)
		{
			sem_wait(philo->output);
			tm = ft_time() - philo->init_time;
			printf("%ld ms %d philo is dead\n", tm, philo->nbr);
			sem_post(philo->death);
			return (NULL);
		}
		else if ((philo->nbr_of_eat != -1)
			&& (philo->nbr_cycle >= philo->nbr_of_eat))
		{
			sem_post(philo->counter);
			return (NULL);
		}
	}
	return (NULL);
}

static void	ft_philo_action(t_data *data, int i)
{
	while (data->philos[i].nbr_cycle != data->nbr_of_eat)
	{
		sem_wait(data->forks);
		data->philos[i].state = 8;
		ft_output(&data->philos[i]);
		sem_wait(data->forks);
		data->philos[i].state = 9;
		ft_output(&data->philos[i]);
		data->philos[i].state = 1;
		data->philos[i].tm_aft_meal = ft_time();
		ft_output(&data->philos[i]);
		ft_usleep(data->time_to_eat);
		if (data->nbr_of_eat != -1)
			data->philos[i].nbr_cycle++;
		sem_post(data->forks);
		sem_post(data->forks);
		if (data->philos[i].nbr_cycle == data->nbr_of_eat)
			return ;
		data->philos[i].state = 2;
		ft_output(&data->philos[i]);
		ft_usleep(data->time_to_sleep);
		data->philos[i].state = 3;
		ft_output(&data->philos[i]);
	}
}

void	ft_philo_bonus(t_data *data, int i)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, ft_check, &data->philos[i]);
	pthread_detach(thread);
	ft_philo_action(data, i);
	ft_usleep(500);
	exit (0);
}

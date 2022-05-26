/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:40:04 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/03 02:20:12 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free(t_data *data, pthread_t *ph_thread)
{
	if (data->philos != NULL)
		free(data->philos);
	if (ph_thread != NULL)
		free(ph_thread);
	if (data->forks != NULL)
		free(data->forks);
}

int	ft_error_msg(t_data *data, pthread_t *ph_thread, int msg)
{
	if (msg == 2)
		return (printf("The wrong number of arguments!\n"));
	ft_free(data, ph_thread);
	if (msg == 1)
		return (printf("Incorrect arrguments!\n"));
	if (msg == -1)
		return (printf("malloc error!\n"));
	return (0);
}

int	ft_free_philo(t_data *data, pthread_t *ph_thread)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&data->output);
	pthread_mutex_destroy(&data->wait);
	ft_free(data, ph_thread);
	return (0);
}

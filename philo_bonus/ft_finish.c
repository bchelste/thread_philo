/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 22:03:39 by bchelste          #+#    #+#             */
/*   Updated: 2021/09/06 13:55:26 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_free(t_data *data)
{
	if (data->pid != NULL)
		free(data->pid);
	if (data->philos != NULL)
		free(data->philos);
}

int	ft_error_msg(t_data *data, int msg)
{
	if (msg == 2)
		return (printf("The wrong number of arguments!\n"));
	ft_free(data);
	if (msg == 1)
		return (printf("Incorrect arrguments!\n"));
	if (msg == -1)
		return (printf("malloc error!\n"));
	return (0);
}

int	ft_finish(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		kill(data->pid[i], SIGTERM);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->output);
	sem_post(data->counter);
	ft_usleep(100);
	sem_close(data->counter);
	sem_close(data->death);
	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("counter");
	sem_unlink("death");
	ft_free(data);
	return (0);
}

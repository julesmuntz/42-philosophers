/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/18 19:38:55 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_stoic *data)
{
	if (data->fork_status[data->left_fork] == AVAILABLE
		&& data->fork_status[data->right_fork] == AVAILABLE)
	{
		data->fork_status[data->left_fork] = BUSY;
		data->fork_status[data->right_fork] = BUSY;
		return (TRUE);
	}
	return (FALSE);
}

int	drop_forks(t_stoic *data)
{
	if (data->fork_status[data->left_fork] == BUSY
		&& data->fork_status[data->right_fork] == BUSY)
	{
		data->fork_status[data->left_fork] = AVAILABLE;
		data->fork_status[data->right_fork] = AVAILABLE;
		return (TRUE);
	}
	return (FALSE);
}

void	*routine(void *ptr)
{
	t_stoic	*data;
	int		i;
	int		lap;

	i = 1;
	lap = 1;
	data = (t_stoic *)ptr;
	while (TRUE)
	{
		if (data->elapsed >= (unsigned long)&data->time_to_die)
		{
			printf("%lu\t%d died\n", data->elapsed, i);
			break ;
		}
		i = 1;
		while (i <= data->number_of_philosophers)
		{
			forks_pos(i, data);
			gettimeofday(&data->present, 0);
			data->elapsed = (data->present.tv_sec - data->start.tv_sec) * 1000;
			data->elapsed += (data->present.tv_usec - data->start.tv_usec)
				/ 1000;
			data->status[i] = THINKING;
			printf("%lu\t%d is thinking\n", data->elapsed, i);
			if (take_forks(data) == TRUE)
			{
				take_forks(data);
				pthread_mutex_lock(&data->forks[data->left_fork]);
				gettimeofday(&data->present, 0);
				printf("%lu\t%d has taken a fork\n", data->elapsed, i);
				pthread_mutex_lock(&data->forks[data->right_fork]);
				gettimeofday(&data->present, 0);
				printf("%lu\t%d has taken a fork\n", data->elapsed, i);
				pthread_mutex_lock(&data->mutex);
				data->status[i] = EATING;
				printf("%lu\t%d is eating\n", data->elapsed, i);
				msleep(data->time_to_eat);
				pthread_mutex_unlock(&data->mutex);
				drop_forks(data);
				pthread_mutex_unlock(&data->forks[data->left_fork]);
				pthread_mutex_unlock(&data->forks[data->right_fork]);
			}
			i++;
		}
		if (lap == data->number_of_times_each_philosopher_must_eat)
			break ;
		lap++;
	}
	return (NULL);
}

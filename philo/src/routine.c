/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/08 16:27:39 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(int philo_id, t_stoic *data)
{
	int	right;
	int	left;

	right = philo_id;
	if (philo_id == 1)
		left = data->number_of_philosophers;
	else
		left = philo_id - 1;
	if (data->fork[left] == AVAILABLE && data->fork[right] == AVAILABLE)
	{
		data->fork[right] = BUSY;
		data->fork[left] = BUSY;
		return (TRUE);
	}
	return (FALSE);
}

int	drop_forks(int philo_id, t_stoic *data)
{
	int	right;
	int	left;

	right = philo_id;
	if (philo_id == 1)
		left = data->number_of_philosophers;
	else
		left = philo_id - 1;
	if (data->fork[left] == BUSY && data->fork[right] == BUSY)
	{
		data->fork[right] = AVAILABLE;
		data->fork[left] = AVAILABLE;
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
		i = 1;
		if (data->elapsed >= (unsigned long)&data->time_to_die)
		{
			printf("%lu\t%d died\n", data->elapsed, i);
			break ;
		}
		while (i <= data->number_of_philosophers)
		{
			gettimeofday(&data->present, 0);
			data->elapsed = (data->present.tv_sec - data->start.tv_sec) * 1000;
			data->elapsed += (data->present.tv_usec - data->start.tv_usec)
				/ 1000;
			if (take_forks(i, data) == TRUE)
			{
				printf("%lu\t%d has taken a fork\n", data->elapsed, i);
				pthread_mutex_lock(&data->mutex);
				printf("%lu\t%d is eating\n", data->elapsed, i);
				msleep(data->time_to_eat);
				pthread_mutex_unlock(&data->mutex);
				drop_forks(i, data);
			}
			else if (take_forks(i, data) == FALSE)
				printf("%lu\t%d is thinking\n", data->elapsed, i);
			i++;
		}
		if (lap == data->number_of_times_each_philosopher_must_eat)
			break ;
		lap++;
	}
	return (NULL);
}

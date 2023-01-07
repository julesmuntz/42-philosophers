/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/07 20:54:56 by julmuntz         ###   ########.fr       */
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

// void	decide(int philo_id, t_stoic *data)
// {
// 	if (take_forks(philo_id, NULL) == TRUE)
// 		data->status[philo_id] = EATING;
// 	else if (drop_forks(philo_id, NULL) == TRUE)
// 		data->status[philo_id] = THINKING;
// }

void	*routine(void *ptr)
{
	t_stoic	*data;
	int		i;
	int		lap;

	i = 1;
	lap = 1;
	data = (t_stoic *)ptr;
	if (!data->number_of_times_each_philosopher_must_eat)
		lap = data->number_of_times_each_philosopher_must_eat + 1;
	while (lap <= data->number_of_times_each_philosopher_must_eat)
	{
		i = 1;
		while (i <= data->number_of_philosophers)
		{
			if (take_forks(i, data) == TRUE)
			{
				pthread_mutex_lock(&data->mutex);
				printf("%d %d has taken a fork\n", data->time, i);
				pthread_mutex_unlock(&data->mutex);
			}
			msleep(data->time_to_eat);
			i++;
		}
		lap++;
	}
	return (NULL);
}

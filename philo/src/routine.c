/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/06 13:53:12 by julmuntz         ###   ########.fr       */
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

void	decide(int philo_id, t_stoic *data)
{
	if (take_forks(philo_id, data) == TRUE)
		data->status = EATING;
	else if (drop_forks(philo_id, data) == TRUE)
		data->status = THINKING;
}

void	*routine(void *ptr)
{
	t_stoic	*data;
	int		i;

	i = 1;
	data = (t_stoic *)ptr;
	while (TRUE)
	{
		while (i <= data->number_of_philosophers)
		{
			if (take_forks(i, &data) == TRUE)
			{
				pthread_mutex_lock(&data->mutex);
				data->test_var++;
				pthread_mutex_unlock(&data->mutex);
			}
			i++;
		}
		i = 1;
	}
	return (NULL);
}

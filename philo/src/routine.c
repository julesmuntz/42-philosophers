/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/04 22:28:51 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(int philo_id, t_stoic *data)
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
	}
}

void	*routine(void *ptr)
{
	t_stoic	*data;
	int		i;

	i = 0;
	data = (t_stoic *)ptr;
	while (i < 100000)
	{
		pthread_mutex_lock(&data->mutex);
		data->test_var++;
		pthread_mutex_unlock(&data->mutex);
		i++;
	}
	return (NULL);
}

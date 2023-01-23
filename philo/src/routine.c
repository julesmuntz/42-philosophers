/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/23 22:23:30 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, TAKING_A_FORK);
		pthread_mutex_lock(&philo->right_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, TAKING_A_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, TAKING_A_FORK);
		pthread_mutex_lock(philo->left_fork);
		gettimeofday(&philo->data->current_time, 0);
		print_status(philo, TAKING_A_FORK);
	}
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	gettimeofday(&philo->last_meal, 0);
	if (philo->id % 2 == 0)
	{
		print_status(philo, THINKING);
		usleep(philo->data->time_to_eat * 1000);
	}
	take_forks(philo);
	print_status(philo, EATING);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	print_status(philo, SLEEPING);
	print_status(philo, THINKING);
	return (NULL);
}

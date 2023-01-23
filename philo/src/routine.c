/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:23:19 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/23 16:54:47 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	gettimeofday(&philo->data->present, 0);
	philo->data->elapsed = (philo->data->present.tv_sec - philo->data->start.tv_sec) * 1000;
	philo->data->elapsed += (philo->data->present.tv_usec - philo->data->start.tv_usec) / 1000;
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%lld\t%d\t%s.\n", philo->data->elapsed, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		printf("%lld\t%d\t%s.\n", philo->data->elapsed, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		printf("%lld\t%d\t%s.\n", philo->data->elapsed, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		printf("%lld\t%d\t%s.\n", philo->data->elapsed, philo->id, "has taken a fork");
	}
}

void	*routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	if (philo->data->elapsed >= philo->data->time_to_die)
		return (printf("%lld\t%d\t%s.\n", philo->data->elapsed, philo->id, "died"),exit(EXIT_SUCCESS), NULL);
	print_status(philo, THINKING);
	take_forks(philo);
	print_status(philo, EATING);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	print_status(philo, SLEEPING);
	return (NULL);
}

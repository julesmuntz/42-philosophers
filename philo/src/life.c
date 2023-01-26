/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:46:47 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/26 18:52:48 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(struct timeval launch_time, struct timeval current_time)
{
	if (launch_time.tv_sec == current_time.tv_sec)
		return ((current_time.tv_usec - launch_time.tv_usec) / 1000);
	return ((((current_time.tv_sec - launch_time.tv_sec - 1) * 1000000)
			+ current_time.tv_usec + 999999 - launch_time.tv_usec) / 1000);
}

int	one_philo(t_philo *philo)
{
	if (philo->data->number_of_philosophers == 1)
	{
		print_status(philo, "has taken a fork");
		usleep((philo->data->time_to_die) * 1000);
		return (TRUE);
	}
	return (FALSE);
}

static int	dead(t_philo *philo, t_stoic *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->lock);
	if (philo->last_meal.tv_sec && get_time(philo->last_meal,
			current_time) > data->time_to_die)
	{
		print_status(philo, "died");
		pthread_mutex_unlock(&philo->lock);
		var_is(EDITED, &data->check_lock, &data->working, FALSE);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

void	life_check(t_philo *philo, t_stoic *data)
{
	int	i;
	int	full;

	while (var_is(CHECKED, &data->check_lock, &data->working, 0) == TRUE)
	{
		i = 0;
		full = 0;
		while (i < data->number_of_philosophers)
		{
			if (dead(&philo[i], data))
				break ;
			if (data->number_of_meals >= 0 && var_is(CHECKED, &philo[i].lock,
					&philo[i].ate_n_times, 0) >= data->number_of_meals)
				full++;
			i++;
		}
		if (full == i)
			var_is(EDITED, &data->check_lock, &data->working, FALSE);
	}
}

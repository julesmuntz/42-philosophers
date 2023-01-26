/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:39:35 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/26 18:55:14 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_philo *philo, int current)
{
	int	i;

	i = 0;
	while (i < current)
	{
		pthread_join(philo[i].philosopher, NULL);
		pthread_mutex_destroy(&philo[i].left_fork);
		pthread_mutex_destroy(&philo[i].lock);
		i++;
	}
}

static int	init_threads(t_philo *philo, int current, t_stoic *data)
{
	if (pthread_mutex_init(&philo[current].left_fork, NULL))
		var_is(EDITED, &data->check_lock, &data->failure, TRUE);
	if (philo[current].id == data->number_of_philosophers)
		philo[current].right_fork = &philo[0].left_fork;
	else
		philo[current].right_fork = &philo[current + 1].left_fork;
	if (pthread_mutex_init(&philo[current].lock, NULL))
	{
		var_is(EDITED, &data->check_lock, &data->failure, TRUE);
		pthread_mutex_destroy(&philo[current].left_fork);
	}
	if (pthread_create(&philo[current].philosopher, NULL, &routine,
			&philo[current]) && data->failure == FALSE)
	{
		var_is(EDITED, &data->check_lock, &data->failure, TRUE);
		pthread_mutex_destroy(&philo[current].left_fork);
		pthread_mutex_destroy(&philo[current].lock);
	}
	if (data->failure == TRUE)
	{
		join_threads(philo, current);
		return (1);
	}
	return (0);
}

static int	create_threads(t_stoic *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i != data->number_of_philosophers)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].ate_n_times = 0;
		philo[i].last_meal.tv_sec = 0;
		if (init_threads(philo, i, data))
			return (1);
		i++;
	}
	return (0);
}

static int	init(t_stoic *data, int arc, char **arv)
{
	int	i;

	i = 1;
	data->stops = FALSE;
	if (arc < 5 || arc > 6)
		return (printf("Error\nInvalid number of arguments. \
It must be 4 or 5, not %d.\n", (arc - 1)), ERROR);
	while (i < arc)
	{
		if ((p_atoi(data, arv[i]) == ERROR))
			invalid_argument(data, i);
		i++;
	}
	data->error = "tbd";
	if (data->stops == TRUE)
		return (ERROR);
	data->number_of_philosophers = p_atoi(data, arv[1]);
	data->time_to_die = p_atoi(data, arv[2]);
	data->time_to_eat = p_atoi(data, arv[3]);
	data->time_to_sleep = p_atoi(data, arv[4]);
	data->number_of_meals = -1;
	if (arc == 6)
		data->number_of_meals = p_atoi(data, arv[5]);
	init_vars(data);
	return (0);
}

int	main(int arc, char **arv)
{
	t_stoic	data;
	t_philo	*philo;

	if (init(&data, arc, arv))
		return (0);
	if (pthread_mutex_init(&data.print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data.check_lock, NULL))
		return (pthread_mutex_destroy(&data.print_lock), 1);
	philo = malloc(sizeof(t_philo) * data.number_of_philosophers);
	if (!philo)
		return (pthread_mutex_destroy(&data.print_lock),
			pthread_mutex_destroy(&data.check_lock), 1);
	if (create_threads(&data, philo))
		return (pthread_mutex_destroy(&data.print_lock),
			pthread_mutex_destroy(&data.check_lock), 1);
	gettimeofday(&data.launch_time, NULL);
	var_is(EDITED, &data.check_lock, &data.launch, TRUE);
	life_check(philo, &data);
	join_threads(philo, data.number_of_philosophers);
	pthread_mutex_destroy(&data.print_lock);
	pthread_mutex_destroy(&data.check_lock);
	free(philo);
	return (0);
}

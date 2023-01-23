/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:39:35 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/23 22:21:01 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	invalid_argument(t_stoic *data, int id)
{
	if (data->stops == FALSE)
		printf("Error\n");
	if (p_strcmp(data->error, "Less than 1") == 0)
		printf("The value of Argument %d is less than 1.\n", id);
	else if (p_strcmp(data->error, "Integer overflow") == 0)
		printf("The value of Argument %d exceeds the INT_MAX.\n", id);
	else if (p_strcmp(data->error, "Not a number") == 0)
		printf("The input of Argument %d is an invalid value.\n", id);
	data->stops = TRUE;
	return ;
}

int	create_threads(t_stoic *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i != data->number_of_philosophers)
	{
		data->died = FALSE;
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].ate_n_times = 0;
		if (pthread_mutex_init(&philo[i].right_fork, NULL))
			return (1);
		if (philo[i].id == 1)
			philo[0].left_fork
				= &philo[data->number_of_philosophers - 1].right_fork;
		else
			philo[i].left_fork = &philo[i - 1].right_fork;
		if (pthread_create(&philo[i].philosopher, NULL, &routine, &philo[i]))
			pthread_mutex_destroy(&philo[i].right_fork);
		i++;
	}
	i = 1;
	while (++i != data->number_of_philosophers)
		if (pthread_join(philo[i].philosopher, NULL))
			return (1);
	return (0);
}

int	init(t_stoic *data, int arc, char **arv)
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
	return (0);
}

int	main(int arc, char **arv)
{
	t_stoic	data;
	t_philo	*philo;

	if (init(&data, arc, arv))
		return (0);
	gettimeofday(&data.launch_time, 0);
	if (pthread_mutex_init(&data.lock, NULL))
		return (1);
	philo = malloc(sizeof(t_philo) * data.number_of_philosophers);
	if (!philo)
		return (pthread_mutex_destroy(&data.lock), 1);
	create_threads(&data, philo);
	if (pthread_mutex_destroy(&data.lock))
		return (1);
	free(philo);
	return (0);
}

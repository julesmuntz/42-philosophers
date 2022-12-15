/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:39:35 by julmuntz          #+#    #+#             */
/*   Updated: 2022/12/15 11:39:35 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	invalid_argument(t_stoic *data, int argument)
{
	if (data->stops == FALSE)
		printf("Error\n");
	if (p_strcmp(data->error, "Less than 1") == 0)
		printf("The value of Argument %d is less than 1.\n", argument);
	else if (p_strcmp(data->error, "Integer overflow") == 0)
		printf("The value of Argument %d exceeds the INT_MAX.\n", argument);
	else if (p_strcmp(data->error, "Not a number") == 0)
		printf("The input of Argument %d is not a valid number.\n", argument);
	data->stops = TRUE;
}

int	main(int arc, char **arv)
{
	t_stoic	data;
	int		i;

	i = 0;
	data.stops = FALSE;
	if (arc < 5 || arc > 6)
		return (printf("Error\n4 or 5 arguments required.\n"), 0);
	while (i++ < arc - 1)
		if ((p_atoi(&data, arv[i]) == ERROR))
			invalid_argument(&data, i);
	if (data.stops == TRUE)
		return (0);
	data.number_of_philosophers = p_atoi(&data, arv[1]);
	data.time_to_die = p_atoi(&data, arv[2]);
	data.time_to_eat = p_atoi(&data, arv[3]);
	data.time_to_sleep = p_atoi(&data, arv[4]);
	data.number_of_times_each_philosopher_must_eat = p_atoi(&data, arv[5]);
	data.philo = malloc(sizeof(int) * data.number_of_philosophers);
	if (!data.philo)
		return (0);
	return (0);
}

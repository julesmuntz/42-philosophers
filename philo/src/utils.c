/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:20:42 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/18 17:30:00 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_atoi(t_stoic *data, char *s)
{
	int		i;
	long	res;
	int		minus;

	i = 0;
	res = 0;
	minus = 0;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	if (s[i] == '-')
		minus = TRUE;
	while (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - 48;
		if ((unsigned long)res > INT_MAX)
			return (data->error = "Integer overflow", ERROR);
		i++;
	}
	if (s[i] != 0)
		return (data->error = "Not a number", ERROR);
	if (res == 0 || minus == TRUE)
		return (data->error = "Less than 1", ERROR);
	return (res);
}

int	p_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	forks_pos(int philo_id, t_stoic *data)
{
	data->right_fork = philo_id;
	if (philo_id == 1)
		data->left_fork = data->number_of_philosophers;
	else
		data->left_fork = philo_id - 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:28:53 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/21 16:29:45 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(int ms)
{
	usleep(ms *= 1000);
}

void	get_time(t_stoic *data)
{
	gettimeofday(&data->present, 0);
	data->elapsed = (data->present.tv_sec - data->start.tv_sec) * 1000;
	data->elapsed += (data->present.tv_usec - data->start.tv_usec)
		/ 1000;
}

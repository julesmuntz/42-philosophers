/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:28:53 by julmuntz          #+#    #+#             */
/*   Updated: 2023/01/23 22:23:50 by julmuntz         ###   ########.fr       */
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

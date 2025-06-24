/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:34:16 by juportie          #+#    #+#             */
/*   Updated: 2025/06/24 08:45:03 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_settings(t_settings *settings, int argc, char *argv[])
{
	settings->number_of_philosophers = arg_to_int(argv[1]);
	if (settings->number_of_philosophers == ERROR)
		return (ERROR);
	settings->time_to_die = arg_to_int(argv[2]);
	if (settings->time_to_die == ERROR)
		return (ERROR);
	settings->time_to_eat = arg_to_int(argv[3]);
	if (settings->time_to_eat == ERROR)
		return (ERROR);
	settings->time_to_sleep = arg_to_int(argv[4]);
	if (settings->time_to_sleep == ERROR)
		return (ERROR);
	if (argc == 6)
	{
		settings->number_of_times_each_philosophers_must_eat
			= arg_to_int(argv[5]);
	}
	else
		settings->number_of_times_each_philosophers_must_eat = UNSET;
	if (settings->number_of_times_each_philosophers_must_eat == ERROR)
		return (ERROR);
	return (0);
}

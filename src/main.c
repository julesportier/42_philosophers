/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:06:58 by juportie          #+#    #+#             */
/*   Updated: 2025/06/23 11:30:31 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	invalid_args(t_settings *settings)
{
	if (settings->number_of_philosophers < 0)
		return (1);
	if (settings->time_to_die < 0)
		return (1);
	if (settings->time_to_eat < 0)
		return (1);
	if (settings->time_to_sleep < 0)
		return (1);
	if (settings->number_of_times_each_philosophers_must_eat < 0)
		return (1);
	return (0);
}

t_settings	convert_args(int argc, char *argv[])
{
	t_settings settings;

	settings.number_of_philosophers = arg_to_int(argv[1]);
	settings.time_to_die = arg_to_int(argv[2]);
	settings.time_to_eat = arg_to_int(argv[3]);
	settings.time_to_sleep = arg_to_int(argv[4]);
	if (argc == 6)
	{
		settings.number_of_times_each_philosophers_must_eat
			= arg_to_int(argv[5]);
	}
	else
		settings.number_of_times_each_philosophers_must_eat = 0;
	return (settings);
}

int	main(int argc, char *argv[])
{
	t_settings settings;

	if (argc < 5 || argc > 6)
		return (print_err("invalid number of arguments"));
	settings = convert_args(argc, argv);
	if (invalid_args(&settings))
		return (-1);
	if (DEBUG)
	{
		printf("number_of_philosophers == %d\n"
				"time_to_die == %d\n"
				"time_to_eat == %d\n"
				"time_to_sleep == %d\n"
				"number_of_times_each_philosophers_must_eat == %d\n",
				settings.number_of_philosophers,
				settings.time_to_die,
				settings.time_to_eat,
				settings.time_to_sleep,
				settings.number_of_times_each_philosophers_must_eat);
	}
	return (0);
}

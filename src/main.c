/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:06:58 by juportie          #+#    #+#             */
/*   Updated: 2025/06/24 08:41:05 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_settings settings;

	if (argc < 5 || argc > 6)
		return (print_err("invalid number of arguments"));
	if (init_settings(&settings, argc, argv) == ERROR)
		return (ERROR);
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

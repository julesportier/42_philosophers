/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:06:58 by juportie          #+#    #+#             */
/*   Updated: 2025/06/30 10:20:57 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int	init_forks(t_fork **forks, int philos_nbr)
{
	int	i;

	*forks = malloc(sizeof(t_fork) * philos_nbr);
	if (!*forks)
		return (print_err("init_forks: mem alloc failure"));
	i = 0;
	while (i < philos_nbr)
	{
		pthread_mutex_init(&(*forks)[i].mutex, NULL);
		(*forks)[i].state = available;
		++i;
	}
	return (0);
}

// Alloc all philos on a unique memory area.
int	init_philos(
	t_philo **philos,
	const t_settings *settings,
	t_fork *forks
)
{
	int		i;

	*philos = malloc(sizeof(t_philo) * settings->number_of_philosophers);
	if (!*philos)
		return (print_err("init_philos: mem alloc failure"));
	i = 0;
	while (i < settings->number_of_philosophers)
	{
		(*philos)[i].id = i;
		(*philos)[i].first_philo = 0;
		// (*philos)[i].state = thinking;
		(*philos)[i].forks = forks;
		(*philos)[i].meals_taken = 0;
		(*philos)[i].settings = settings;
		++i;
	}
	return (0);
}

static void	init_philos_last_meal(t_philo *philos)
{
	int	i;
	int	philos_nbr;

	i = 0;
	philos_nbr = (*philos).settings->number_of_philosophers;
	while (i < philos_nbr)
	{
		philos[i].last_meal = philos[i].settings->start_time;
		++i;
	}
}


int	start_simulation(t_settings *settings, t_philo *philos)
{
	pthread_t		*threads;

	if (alloc_threads(&threads, settings->number_of_philosophers) == ERROR)
		return (print_err("start_simulation: threads mem alloc failure"));
	settings->start_time = get_time();
	init_philos_last_meal(philos);

#if (DEBUG && DBG_SIM)
	printf("start time == %llu us\n", settings->start_time);
#endif

	if (init_threads(
			threads,
			philos,
			settings->number_of_philosophers
		) == ERROR
	)
	{
		free(threads);
		return (ERROR);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_settings 	settings;
	t_fork		*forks;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (print_err("invalid number of arguments"));
	if (init_settings(&settings, argc, argv) == ERROR)
		return (ERROR);
	if (init_forks(&forks, settings.number_of_philosophers) == ERROR)
	 	return (ERROR);

#if (DEBUG && DBG_MAIN)
	printf("number_of_philosophers == %d\n"
			"time_to_die == %d\n"
			"time_to_eat == %d\n"
			"time_to_sleep == %d\n"
			"number_of_times_each_philosophers_must_eat == %d\n"
			"start_time == %llu us\n",
			settings.number_of_philosophers,
			settings.time_to_die,
			settings.time_to_eat,
			settings.time_to_sleep,
			settings.number_of_times_each_philosophers_must_eat,
			settings.start_time);
#endif

	// init_monitor();
	if (init_philos(&philos, (const t_settings *)&settings, forks) == ERROR)
	{
		free(forks);
		return (ERROR);
	}
	start_simulation(&settings, philos);
	return (0);
}

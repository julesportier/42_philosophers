/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:06:58 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 09:13:56 by juportie         ###   ########.fr       */
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
		if (pthread_mutex_init(&(*forks)[i].mutex, NULL))
			return (print_err("init_forks: mutex init failure"));
#if DEBUG && DBG_FORK
	printf("init_forks mutex %d == %p\n", i, &(*forks)[i].mutex);
#endif
		(*forks)[i].state = available;
		++i;
	}
	return (0);
}

// Alloc all philos on a unique memory area.
int	init_philos(
	t_philo **philos,
	t_shared *shared,
	t_fork *forks
)
{
	int		i;

	*philos = malloc(sizeof(t_philo) * shared->philos_nbr);
	if (!*philos)
		return (print_err("init_philos: mem alloc failure"));
	i = 0;
	while (i < shared->philos_nbr)
	{
		(*philos)[i].id = i;
		(*philos)[i].first_philo = 0;
		// (*philos)[i].state = thinking;
		(*philos)[i].forks = forks;
		(*philos)[i].owned_forks[0] = 0;
		(*philos)[i].owned_forks[1] = 0;
		(*philos)[i].meals_taken = 0;
		(*philos)[i].shared = shared;
		++i;
	}
	return (0);
}

static void	init_philos_last_meal(t_philo *philos)
{
	int	i;
	int	philos_nbr;

	i = 0;
	philos_nbr = (*philos).shared->philos_nbr;
	while (i < philos_nbr)
	{
		philos[i].last_meal = philos[i].shared->start_time;
		++i;
	}
}


int	start_simulation(t_shared *shared, t_philo *philos)
{
	pthread_t		*threads;

	if (alloc_threads(&threads, shared->philos_nbr) == ERROR)
		return (print_err("start_simulation: threads mem alloc failure"));
	shared->start_time = get_time();
	init_philos_last_meal(philos);

#if (DEBUG && DBG_SIM)
	printf("start time == %llu us\n", shared->start_time);
#endif

	if (init_threads(
			threads,
			philos,
			shared->philos_nbr
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
	t_shared 	shared;
	t_fork		*forks = NULL;
	t_philo		*philos = NULL;

	if (argc < 5 || argc > 6)
		return (print_err("invalid number of arguments"));
	if (init_shared(&shared, argc, argv) == ERROR)
		return (ERROR);
	if (init_forks(&forks, shared.philos_nbr) == ERROR)
	{
		deinit_shared_mutexes(&shared);
	 	return (ERROR);
	}

#if (DEBUG && DBG_MAIN)
	printf("number_of_philosophers == %d\n"
			"time_to_die == %d\n"
			"time_to_eat == %d\n"
			"time_to_sleep == %d\n"
			"number_of_times_each_philosophers_must_eat == %d\n"
			"start_time == %llu us\n",
			shared.number_of_philosophers,
			shared.time_to_die,
			shared.time_to_eat,
			shared.time_to_sleep,
			shared.number_of_times_each_philosophers_must_eat,
			shared.start_time);
#endif

	// init_monitor();
	if (init_philos(&philos, (t_shared *)&shared, forks) == ERROR)
	{
		deinit_shared_mutexes(&shared);
		free_forks(forks, shared.philos_nbr);
		return (ERROR);
	}
	start_simulation(&shared, philos);
	deinit_shared_mutexes(&shared);
	free_forks(forks, shared.philos_nbr);
	free(philos);
	return (0);
}

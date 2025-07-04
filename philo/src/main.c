/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:06:58 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 14:40:07 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	init_forks(t_fork **forks, int philos_nbr)
{
	int	i;

	*forks = malloc(sizeof(t_fork) * philos_nbr);
	if (!*forks)
		return (print_err("init_forks: mem alloc failure\n"));
	i = 0;
	while (i < philos_nbr)
	{
		(*forks)[i].state = available;
		if (pthread_mutex_init(&(*forks)[i].mutex, NULL))
		{
			free_forks(*forks, i);
			return (print_err("init_forks: mutex init failure\n"));
		}
		++i;
	}
	return (0);
}

int	init_philos(
	t_philo **philos,
	t_shared *shared,
	t_fork *forks
)
{
	int		i;

	*philos = malloc(sizeof(t_philo) * shared->philos_nbr);
	if (!*philos)
		return (print_err("init_philos: mem alloc failure\n"));
	i = 0;
	while (i < shared->philos_nbr)
	{
		(*philos)[i].id = i;
		(*philos)[i].forks = forks;
		(*philos)[i].owned_forks[0] = 0;
		(*philos)[i].owned_forks[1] = 0;
		(*philos)[i].meals_taken = 0;
		(*philos)[i].shared = shared;
		++i;
	}
	return (0);
}

int	start_simulation(t_shared *shared, t_philo *philos)
{
	pthread_t		*threads;

	if (alloc_threads(&threads, shared->philos_nbr) == ERROR)
		return (ERROR);
	if (init_threads(threads, philos, shared) == ERROR)
	{
		free(threads);
		return (ERROR);
	}
	free(threads);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_shared	shared;
	t_fork		*forks;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (print_err("philo: invalid number of arguments\n"));
	if (init_shared(&shared, argc, argv) == ERROR)
		return (ERROR);
	if (shared.philos_nbr == 0 || shared.meals_nbr == 0)
		return (0);
	if (init_forks(&forks, shared.philos_nbr) == ERROR)
	{
		deinit_shared_mutexes(&shared);
		return (ERROR);
	}
	if (init_philos(&philos, (t_shared *)&shared, forks) == ERROR)
	{
		deinit_shared_mutexes(&shared);
		free_forks(forks, shared.philos_nbr);
		return (ERROR);
	}
	start_simulation(&shared, philos);
	return (free_all(&shared, forks, philos));
}

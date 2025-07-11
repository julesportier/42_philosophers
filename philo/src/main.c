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
	t_parameters *parameters,
	t_fork *forks
)
{
	int		i;

	*philos = malloc(sizeof(t_philo) * parameters->philos_nbr);
	if (!*philos)
		return (print_err("init_philos: mem alloc failure\n"));
	i = 0;
	while (i < parameters->philos_nbr)
	{
		(*philos)[i].id = i;
		(*philos)[i].forks = forks;
		(*philos)[i].owned_forks[0] = 0;
		(*philos)[i].owned_forks[1] = 0;
		if (pthread_mutex_init(&(*philos)[i].meals.mutex, NULL))
		{
			free_philos(*philos, i);
			return (ERROR);
		}
		(*philos)[i].meals.done = 0;
		(*philos)[i].meals.last = get_time();
		(*philos)[i].parameters = parameters;
		++i;
	}
	return (0);
}

int	start_simulation(t_parameters *shared, t_philo *philos)
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
	t_parameters	parameters;
	t_fork			*forks;
	t_philo			*philos;

	if (argc < 5 || argc > 6)
		return (print_err("philo: invalid number of arguments\n"));
	if (init_parameters(&parameters, argc, argv) == ERROR)
		return (ERROR);
	if (parameters.philos_nbr == 0 || parameters.meals_nbr == 0)
		return (0);
	if (init_forks(&forks, parameters.philos_nbr) == ERROR)
	{
		deinit_sim_mutex(&parameters);
		return (ERROR);
	}
	if (init_philos(&philos, &parameters, forks) == ERROR)
	{
		deinit_sim_mutex(&parameters);
		free_forks(forks, parameters.philos_nbr);
		return (ERROR);
	}
	if (start_simulation(&parameters, philos) == ERROR)
		return (free_all(&parameters, forks, philos, ERROR));
	return (free_all(&parameters, forks, philos, 0));
}

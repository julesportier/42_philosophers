/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:06:58 by juportie          #+#    #+#             */
/*   Updated: 2025/07/09 11:04:36 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

int	alloc_threads(pthread_t **threads, int philos_nbr)
{
	*threads = malloc(sizeof(pthread_t) * (philos_nbr + 1));
	if (!*threads)
		return (print_err("alloc_threads: mem alloc failure\n"));
	memset(*threads, 0, sizeof(pthread_t) * philos_nbr);
	return (0);
}

static int	join_threads(pthread_t *threads, t_parameters *parameters)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < parameters->philos_nbr)
	{
		if (pthread_join(threads[i], NULL))
		{
			pthread_mutex_lock(&parameters->sim.mutex);
			if (parameters->sim.state == running)
			{
				ret = print_err("join_threads: join thread failure\n");
				parameters->sim.state = stop;
			}
			pthread_mutex_unlock(&parameters->sim.mutex);
		}
		++i;
	}
	return (ret);
}

static int	create_threads(
	pthread_t *threads,
	t_philo *philos,
	t_parameters *parameters)
{
	int	i;

	pthread_mutex_lock(&parameters->sim.mutex);
	i = 0;
	while (i < parameters->philos_nbr)
	{
		if (pthread_create(&threads[i], NULL, routine, &philos[i]))
		{
			parameters->sim.state = stop;
			pthread_mutex_unlock(&parameters->sim.mutex);
			print_err("create_threads: thread creation failure\n");
			return (ERROR);
		}
		++i;
	}
	if (pthread_create(&threads[i], NULL, routine_monitor, philos))
	{
		parameters->sim.state = stop;
		pthread_mutex_unlock(&parameters->sim.mutex);
		print_err("create_threads: thread creation failure\n");
		return (ERROR);
	}
	parameters->start_time = get_time();
	pthread_mutex_unlock(&parameters->sim.mutex);
	return (0);
}

int	init_threads(
	pthread_t *threads,
	t_philo *philos,
	t_parameters *parameters)
{
	int	ret;

	ret = 0;
	if (create_threads(threads, philos, parameters) == ERROR)
		ret = ERROR;
	if (join_threads(threads, parameters) == ERROR)
		ret = ERROR;
	return (ret);
}

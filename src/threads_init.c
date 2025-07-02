/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:06:58 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 14:26:44 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	alloc_threads(pthread_t **threads, int philos_nbr)
{
	*threads = malloc(sizeof(pthread_t) * philos_nbr);
	if (!*threads)
		return (print_err("alloc_threads: mem alloc failure\n"));
	return (0);
}

static int	join_threads(pthread_t *threads, int philos_nbr)
{
	int	i;

	i = 0;
	while (i < philos_nbr)
	{
		if (pthread_join(threads[i], NULL))
		{
			// SEND DEATH TO ALL THREADS
			return (ERROR);
		}
		++i;
	}
	return (0);
}

static int	create_threads(
	pthread_t *threads,
	t_philo *philos,
	int philos_nbr)
{
	int	i;

	i = 0;
	while (i < philos_nbr)
	{
		if (pthread_create(&threads[i], NULL, routine, &philos[i]))
		{
			// SEND DEATH TO ALREADY ALLOCATED THREADS
			return (ERROR);
		}
		++i;
	}
	return (0);
}

int	init_threads(
	pthread_t *threads,
	t_philo *philos,
	int philos_nbr)
{
	if (create_threads(threads, philos, philos_nbr)
		== ERROR)
		return (ERROR);
	if (join_threads((pthread_t *)threads, philos_nbr)
		== ERROR)
		return (ERROR);
	return (0);
}

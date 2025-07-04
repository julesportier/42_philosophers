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
#include <string.h>

int	alloc_threads(pthread_t **threads, int philos_nbr)
{
	*threads = malloc(sizeof(pthread_t) * philos_nbr);
	if (!*threads)
		return (print_err("alloc_threads: mem alloc failure\n"));
	memset(*threads, 0, sizeof(pthread_t) * philos_nbr);
	return (0);
}

static int	join_threads(pthread_t *threads, t_shared *shared)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < shared->philos_nbr)
	{
		if (pthread_join(threads[i], NULL))
		{
			pthread_mutex_lock(&shared->death.mutex);
			if (shared->death.state != dead)
			{
				ret = print_err("join_threads: join thread failure\n");
				shared->death.state = dead;
			}
			pthread_mutex_unlock(&shared->death.mutex);
		}
		++i;
	}
	return (ret);
}

static int	create_threads(
	pthread_t *threads,
	t_philo *philos,
	t_shared *shared)
{
	int	i;
	int	ret;

	pthread_mutex_lock(&shared->death.mutex);
	ret = 0;
	i = 0;
	while (i < shared->philos_nbr)
	{
		if (pthread_create(&threads[i], NULL, routine, &philos[i]))
		{
			shared->death.state = dead;
			print_err("create_threads: thread creation failure\n");
			ret = ERROR;
			break ;
		}
		++i;
	}
	shared->start_time = get_time();
	pthread_mutex_unlock(&shared->death.mutex);
	return (ret);
}

int	init_threads(
	pthread_t *threads,
	t_philo *philos,
	t_shared *shared)
{
	int	ret;

	ret = 0;
	if (create_threads(threads, philos, shared) == ERROR)
		ret = ERROR;
	if (join_threads(threads, shared) == ERROR)
		ret = ERROR;
	return (ret);
}

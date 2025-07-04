/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:00:01 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 13:30:23 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

int	deinit_shared_mutexes(t_shared *shared)
{
	if (pthread_mutex_destroy(&shared->death.mutex))
		return (ERROR);
	return (0);
}

int	free_forks(t_fork *forks, int philos_nbr)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < philos_nbr)
	{
		if (pthread_mutex_destroy(&forks[i].mutex))
			ret = ERROR;
		++i;
	}
	free(forks);
	return (ret);
}

int	free_all(t_shared *shared, t_fork *forks, t_philo *philos)
{
	int	ret;

	ret = 0;
	if (shared)
		ret = deinit_shared_mutexes(shared);
	if (shared && forks)
	{
		if (free_forks(forks, shared->philos_nbr) == ERROR)
			ret = ERROR;
	}
	if (philos)
		free(philos);
	return (ret);
}

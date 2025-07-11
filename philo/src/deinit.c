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

int	deinit_sim_mutex(t_parameters *parameters)
{
	if (pthread_mutex_destroy(&parameters->sim.mutex))
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

int	free_philos(t_philo *philos, int philos_nbr)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < philos_nbr)
	{
		if (pthread_mutex_destroy(&philos[i].meals.mutex))
			ret = ERROR;
		++i;
	}
	free(philos);
	return (ret);
}

int	free_all(
	t_parameters *parameters,
	t_fork *forks,
	t_philo *philos,
	int error)
{
	int	ret;

	ret = error;
	if (parameters)
		ret = deinit_sim_mutex(parameters);
	if (parameters && forks)
	{
		if (free_forks(forks, parameters->philos_nbr) == ERROR)
			ret = ERROR;
	}
	if (parameters && philos)
	{
		if (free_philos(philos, parameters->philos_nbr) == ERROR)
			ret = ERROR;
	}
	return (ret);
}

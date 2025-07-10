/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/09 11:22:38 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	all_philos_repleted(
	t_philo *philo,
	t_parameters *parameters,
	int *philos_repleted)
{
	if (philo->parameters->meals_nbr != UNSET
		&& philo->meals.done >= philo->parameters->meals_nbr)
	{
		*philos_repleted += 1;
		if (*philos_repleted >= parameters->philos_nbr)
		{
			parameters->sim.state = stop;
			return (1);
		}
	}
	return (0);
}

static void	set_simulation_end(t_sim *sim, t_philo *philo)
{
	if (sim->state == running)
	{
		print_death_timestamp(philo);
		sim->state = stop;
	}
}

static int	must_stop_simulation(
	t_philo *philo,
	t_parameters *parameters,
	int *philos_repleted)
{
	pthread_mutex_lock(&philo->meals.mutex);
	pthread_mutex_lock(&parameters->sim.mutex);
	if (reached_time(philo->meals.last, parameters->time_to_die))
	{
		set_simulation_end(&parameters->sim, philo);
		pthread_mutex_unlock(&parameters->sim.mutex);
		pthread_mutex_unlock(&philo->meals.mutex);
		return (1);
	}
	if (all_philos_repleted(philo, parameters, philos_repleted))
	{
		set_simulation_end(&parameters->sim, philo);
		pthread_mutex_unlock(&parameters->sim.mutex);
		pthread_mutex_unlock(&philo->meals.mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meals.mutex);
	pthread_mutex_unlock(&parameters->sim.mutex);
	return (0);
}

void	*routine_monitor(void *all_philos)
{
	t_philo			*philos;
	t_parameters	*parameters;
	int				i;
	int				philos_repleted;

	philos = (t_philo *)all_philos;
	parameters = philos->parameters;
	if (is_sim_end(&philos->parameters->sim))
		return (0);
	while (1)
	{
		i = 0;
		philos_repleted = 0;
		while (i < parameters->philos_nbr)
		{
			if (must_stop_simulation(&philos[i], parameters, &philos_repleted))
				return (0);
			++i;
		}
		usleep(WAIT_TIME);
	}
}

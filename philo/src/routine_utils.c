/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/09 11:11:26 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_even(int i)
{
	if (i % 2 == 0)
		return (1);
	else
		return (0);
}

void	set_simulation_end(t_sim *sim, t_philo *philo)
{
	// pthread_mutex_lock(&sim->mutex);
	if (sim->state == running)
	{
		print_death_timestamp(philo);
		sim->state = stop;
	}
	// pthread_mutex_unlock(&sim->mutex);
}

int	is_sim_end(t_sim *sim)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&sim->mutex);
	if (sim->state == stop)
		ret = 1;
	pthread_mutex_unlock(&sim->mutex);
	return (ret);
}

int	reached_time(unsigned long long start_time, int time)
{
	if ((int)get_elapsed_time_ms(start_time) >= time)
		return (1);
	else
		return (0);
}

// void	check_meals_nbr(t_philo *philo)
// {
// 	if (philo->parameters->meals_nbr != UNSET
// 		&& philo->meals.done >= philo->parameters->meals_nbr)
// 	{
// 		pthread_mutex_lock(&philo->parameters->sim.mutex);
// 		++philo->parameters->sim.philos_done;
// 		if (philo->parameters->sim.philos_done == philo->parameters->philos_nbr)
// 			philo->parameters->sim.state = stop;
// 		pthread_mutex_unlock(&philo->parameters->sim.mutex);
// 	}
// }

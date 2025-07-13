/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/09 11:25:47 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	eat_philo(t_philo *philo)
{
	philo->meals.last = get_time();
	print_timestamp("is eating", philo);
	pthread_mutex_unlock(&philo->meals.mutex);
	while (!reached_time(philo->meals.last, philo->parameters->time_to_eat))
	{
		usleep(WAIT_TIME);
		if (is_sim_end(&philo->parameters->sim))
		{
			release_forks(philo);
			return (SIM_END);
		}
	}
	increment_meals(philo);
	release_forks(philo);
	return (0);
}

static int	sleep_philo(t_philo *philo)
{
	unsigned long long	start_time;

	start_time = get_time();
	print_timestamp("is sleeping", philo);
	while (!reached_time(start_time, philo->parameters->time_to_sleep))
	{
		usleep(WAIT_TIME);
		if (is_sim_end(&philo->parameters->sim))
			return (SIM_END);
	}
	return (0);
}

// We check if the philo owns the two forks twice in the while loop
// to ensure that any taking order works the same.
// e.g.		misses fork 0 ; take fork 1 ; take fork 0 ; break
// (don't:	misses fork 0 ; take fork 1 ; take fork 0 ;
// retry taking already owned fork 1 ; break)
static int	think_philo(t_philo *philo)
{
	print_timestamp("is thinking", philo);
	while (1)
	{
		usleep(WAIT_TIME);
		if (is_sim_end(&philo->parameters->sim))
		{
			release_forks(philo);
			return (SIM_END);
		}
		if (!philo->owned_forks[0])
			try_take_fork(right_fork(philo), philo, 0);
		if (philo->owned_forks[0] && philo->owned_forks[1])
		{
			pthread_mutex_lock(&philo->meals.mutex);
			break ;
		}
		if (!philo->owned_forks[1])
			try_take_fork(left_fork(philo), philo, 1);
		if (philo->owned_forks[0] && philo->owned_forks[1])
		{
			pthread_mutex_lock(&philo->meals.mutex);
			break ;
		}
	}
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	pthread_mutex_lock(&philo->meals.mutex);
	if (is_sim_end(&philo->parameters->sim))
	{
		pthread_mutex_unlock(&philo->meals.mutex);
		return (0);
	}
	init_last_meal(philo);
	if (!is_even(philo->id))
	{
		if (sleep_philo(philo) == SIM_END)
			return (0);
	}
	while (1)
	{
		if (think_philo(philo) == SIM_END)
			return (0);
		if (eat_philo(philo) == SIM_END)
			return (0);
		if (sleep_philo(philo) == SIM_END)
			return (0);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 14:03:34 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	start_eating(t_philo *philo)
{
	philo->last_meal = get_time();
	print_timestamp("is eating", philo);
	while (!is_end_of_simulation(&philo->shared->sim))
	{
		usleep(WAIT_TIME);
		if (reached_time(philo->last_meal, philo->shared->time_to_eat))
			break ;
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_simulation_end(&philo->shared->sim, philo);
	}
	release_forks(philo);
	philo->meals_taken += 1;
	return (0);
}

static int	start_sleeping(t_philo *philo)
{
	unsigned long long	start_time;

	start_time = get_time();
	print_timestamp("is sleeping", philo);
	while (!is_end_of_simulation(&philo->shared->sim)
		&& !reached_time(start_time, philo->shared->time_to_sleep))
	{
		usleep(WAIT_TIME);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
		{
			set_simulation_end(&philo->shared->sim, philo);
			return (DEAD);
		}
	}
	return (0);
}

static int	start_thinking(t_philo *philo)
{
	if (reached_time(philo->last_meal, philo->shared->time_to_die))
	{
		set_simulation_end(&philo->shared->sim, philo);
		return (DEAD);
	}
	print_timestamp("is thinking", philo);
	while (!is_end_of_simulation(&philo->shared->sim))
	{
		usleep(WAIT_TIME);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
		{
			set_simulation_end(&philo->shared->sim, philo);
			release_forks(philo);
			return (DEAD);
		}
		if (!philo->owned_forks[0])
			try_take_fork(right_fork(philo), philo, 0);
		if (philo->owned_forks[0] && philo->owned_forks[1])
			break ;
		if (!philo->owned_forks[1])
			try_take_fork(left_fork(philo), philo, 1);
		if (philo->owned_forks[0] && philo->owned_forks[1])
			break ;
	}
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (is_end_of_simulation(&philo->shared->sim))
		return (0);
	philo->last_meal = philo->shared->start_time;
	if (!is_even(philo->id))
	{
		if (start_sleeping(philo) == DEAD)
			return (0);
	}
	while (1)
	{
		if (start_thinking(philo) == DEAD)
			return (0);
		start_eating(philo);
		if (is_end_of_simulation(&philo->shared->sim)
			|| eaten_enough_meals(philo))
			return (0);
		if (start_sleeping(philo) == DEAD)
			return (0);
	}
	return (0);
}

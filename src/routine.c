/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 09:56:28 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

#if (DEBUG && DBG_ROUTINE)
	#include <stdio.h>
#endif

static int	start_eating(t_philo *philo)
{
	unsigned long long	start_time;

	start_time = get_time();
	if (print_timestamp("is eating", philo) == ERROR)
		return (ERROR);
	while (!death_happened(&philo->shared->death)
		&& !reached_time(start_time, philo->shared->time_to_eat))
	{
		if (usleep(DEAD_CHECK_FREQ) == ERROR)
			return (ERROR);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);
	}
	release_forks(philo);
	philo->meals_taken += 1;
	philo->last_meal = get_time();
	++philo->meals_taken;
	// check number of meals if needed
	// ++philo->first_philo;
	philo->last_meal = get_time();
	return (0);
}

static int	start_sleeping(t_philo *philo)
{
	unsigned long long	start_time;

	start_time = get_time();
	if (print_timestamp("is sleeping", philo) == ERROR)
		return (ERROR);
	while (!death_happened(&philo->shared->death)
		&& !reached_time(start_time, philo->shared->time_to_sleep))
	{
		if (usleep(DEAD_CHECK_FREQ) == ERROR)
			return (ERROR);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);
	}
	return (0);
}

// Used to simplify threads synchronization.
// int	calc_think_padding(t_shared *shared)
// {
// 	if (shared->time_to_eat > shared->time_to_sleep)
// 		return (shared->time_to_eat - shared->time_to_sleep);
// 	else
// 		return (shared->time_to_sleep - shared->time_to_eat);
// }

static int	start_thinking(t_philo *philo)
{
	if (print_timestamp("is thinking", philo))
		return (ERROR);
	// USELESS SLEEPS:
	// usleep(THINKING_PADDING);
	// usleep(calc_think_padding(philo->shared));
	// ADD A WAY TO KNOW OWNED FORKS INSIDE PHILO AND TRY TO TAKE FORKS UNTIL THIS
	while (!philo->owned_forks[0] || !philo->owned_forks[1])
	{
		usleep(DEAD_CHECK_FREQ);
		if (death_happened(&philo->shared->death))
			return (0);
		if (!philo->owned_forks[0])
			if (try_take_fork(right_fork(philo), &philo->owned_forks[0]) == ERROR)
				return (ERROR);
		if (!philo->owned_forks[1])
			if (try_take_fork(left_fork(philo), &philo->owned_forks[1]) == ERROR)
				return (ERROR);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);

#if (DEBUG && DBG_ROUTINE)
	usleep(200 * 1000);
	printf(
		"start_thinking philo %d philo->owned_forks[0] == %d ; philo->owned_forks[1] == %d\n",
		philo->id,
		philo->owned_forks[0],
		philo->owned_forks[1]);
#endif
	
	}
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (!is_even(philo->id))
	{
		start_sleeping(philo);

#if (DEBUG && DBG_ROUTINE)
	usleep(200 * 1000);
	printf(
		"start_thinking philo %d philo->owned_forks[0] == %d ; philo->owned_forks[1] == %d\n",
		philo->id,
		philo->owned_forks[0],
		philo->owned_forks[1]);
#endif
	}
	while (1)
	{
		if (death_happened(&philo->shared->death))
			return (0);
		start_thinking(philo);
		if (death_happened(&philo->shared->death))
			return (0);
		start_eating(philo);
		if (death_happened(&philo->shared->death))
			return (0);
		start_sleeping(philo);
	}
	return (0);
}

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
	if (print_timestamp("is eating", philo) == ERROR)
		return (ERROR);
	philo->last_meal = get_time();
	while (!death_happened(&philo->shared->death)
		&& !reached_time(philo->last_meal, philo->shared->time_to_eat))
	{
		if (usleep(WAIT_TIME) == ERROR)
			return (ERROR);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);
	}
	release_forks(philo);
	philo->meals_taken += 1;
	return (0);
}

static int	start_sleeping(t_philo *philo)
{
	unsigned long long	start_time;

	start_time = get_time();
	if (reached_time(philo->last_meal, philo->shared->time_to_die))
		set_death(&philo->shared->death, philo);
	if (print_timestamp("is sleeping", philo) == ERROR)
		return (ERROR);
	while (!death_happened(&philo->shared->death)
		&& !reached_time(start_time, philo->shared->time_to_sleep))
	{
		if (usleep(WAIT_TIME) == ERROR)
			return (ERROR);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);
	}
	return (0);
}

static int	start_thinking(t_philo *philo)
{
	if (reached_time(philo->last_meal, philo->shared->time_to_die))
		set_death(&philo->shared->death, philo);
	if (print_timestamp("is thinking", philo))
		return (ERROR);
	usleep(WAIT_TIME);
	while (!philo->owned_forks[0] || !philo->owned_forks[1])
	{
		usleep(WAIT_TIME);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);
		if (death_happened(&philo->shared->death))
			return (0);
		if (!philo->owned_forks[0])
			if (try_take_fork(right_fork(philo), philo, 0) == ERROR)
				return (ERROR);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);
		if (death_happened(&philo->shared->death))
			return (0);
		if (!philo->owned_forks[1])
			if (try_take_fork(left_fork(philo), philo, 1) == ERROR)
				return (ERROR);
	}
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (pthread_mutex_lock(&philo->shared->block_mutex))
		return (0);
	if (pthread_mutex_unlock(&philo->shared->block_mutex))
		return (0);
	if (death_happened(&philo->shared->death))
		return (0);
	philo->last_meal = philo->shared->start_time;
	if (!is_even(philo->id))
		start_sleeping(philo);
	while (1)
	{
		if (death_happened(&philo->shared->death))
			return (0);
		start_thinking(philo);
		if (death_happened(&philo->shared->death))
			return (0);
		start_eating(philo);
		if (death_happened(&philo->shared->death) || eaten_enough_meals(philo))
			return (0);
		start_sleeping(philo);
	}
	return (0);
}

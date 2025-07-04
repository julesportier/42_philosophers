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
	while (!death_happened(&philo->shared->death))
	{
		usleep(WAIT_TIME);
		if (reached_time(philo->last_meal, philo->shared->time_to_eat))
			break ;
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
	print_timestamp("is sleeping", philo);
	while (!death_happened(&philo->shared->death)
		&& !reached_time(start_time, philo->shared->time_to_sleep))
	{
		usleep(WAIT_TIME);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);
	}
	return (0);
}

static int	start_thinking(t_philo *philo)
{
	if (reached_time(philo->last_meal, philo->shared->time_to_die))
		set_death(&philo->shared->death, philo);
	print_timestamp("is thinking", philo);
	while (!philo->owned_forks[0] || !philo->owned_forks[1])
	{
		usleep(WAIT_TIME);
		if (!philo->owned_forks[0])
			try_take_fork(right_fork(philo), philo, 0);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);
		if (death_happened(&philo->shared->death))
			return (0);
		if (!philo->owned_forks[1])
			try_take_fork(left_fork(philo), philo, 1);
		if (reached_time(philo->last_meal, philo->shared->time_to_die))
			set_death(&philo->shared->death, philo);
		if (death_happened(&philo->shared->death))
			return (0);
	}
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
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

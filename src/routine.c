/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/06/30 15:17:30 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

// int	get_fork_state(t_fork_state	*state, t_fork *fork)
// {
// 	if (pthread_mutex_lock(&fork->mutex))
// 	{
// 		// SET DEAD ?? WHAT TO FREE ??
// 		return (print_err("get_fork_state: mutex lock failed"));
// 	}
// 	*state = fork->state;
// 	if (pthread_mutex_unlock(&fork->mutex))
// 	{
// 		// SET DEAD ?? WHAT TO FREE ??
// 		return (print_err("get_fork_state: mutex unlock failed"));
// 	}
// 	return (0);
// }
//
// int	set_fork(t_fork_state state, t_fork *fork)
// {
// 	if (pthread_mutex_lock(&fork->mutex))
// 	{
// 		// SET DEAD ?? WHAT TO FREE ??
// 		return (print_err("set_fork: mutex lock failed"));
// 	}
// 	fork->state = state;
// 	if (pthread_mutex_unlock(&fork->mutex))
// 	{
// 		// SET DEAD ?? WHAT TO FREE ??
// 		return (print_err("set_fork: mutex unlock failed"));
// 	}
// 	return (0);
// }

static int	eats_first(t_philo *philo)
{
	int	philos_nbr;

	philos_nbr = philo->settings->number_of_philosophers;
	if (philo->id + 1 != philos_nbr && philo->id % 2 == 0)
		return (1);
	else
		return (0);
}

// static int	sleep_while_all_alive(int time_to_eat, t_death *death)
// {
//

static void	start_eating(t_philo *philo)
{
	print_timestamp("is eating", philo);
	usleep(philo->settings->time_to_eat * 1000);// REGULARLY CHECK DEATH
	// PROTECT THIS FUNCTION
	release_forks(
		&philo->forks[
			calc_first_fork(philo->id, philo->settings->number_of_philosophers)],
		&philo->forks[
			calc_second_fork(philo->id, philo->settings->number_of_philosophers)]);
	philo->meals_taken += 1;
	philo->last_meal = get_time();
	++philo->meals_taken;
	// check number of meals if needed
	++philo->first_philo;
	philo->last_meal = get_time();
}

static void	start_sleeping(t_philo *philo)
{
	print_timestamp("is sleeping", philo);
	usleep(philo->settings->time_to_sleep * 1000);// REGULARLY CHECK DEATH
}

// Used to simplify threads synchronization.
int	calc_think_padding(const t_settings *settings)
{
	if (settings->time_to_eat > settings->time_to_sleep)
		return (settings->time_to_eat - settings->time_to_sleep);
	else
		return (settings->time_to_sleep - settings->time_to_eat);
}

static int	start_thinking(t_philo *philo)
{
	print_timestamp("is thinking", philo);
	usleep(THINKING_PADDING);
	usleep(calc_think_padding(philo->settings));
	// ADD A WAY TO KNOW OWNED FORKS INSIDE PHILO AND TRY TO TAKE FORKS UNTIL THIS
	take_forks(
		&philo->forks[
			calc_first_fork(philo->id, philo->settings->number_of_philosophers)],
		&philo->forks[
			calc_second_fork(philo->id, philo->settings->number_of_philosophers)]);
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (!eats_first(philo))
	{
		if (philo->settings->number_of_philosophers > 1
			&& !is_even(philo->settings->number_of_philosophers)
			&& philo->id == philo->settings->number_of_philosophers - 1)
			start_sleeping(philo);
		start_thinking(philo);
	}
	while (1)
	{
		start_eating(philo);
		// Sleep time while checking death
		start_sleeping(philo);
		// Think while checking forks availability (lock it when available) and death (inner and outter)
		start_thinking(philo);
		// Eat time while checking death (unlock mutex at the end)
	}
}

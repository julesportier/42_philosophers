/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork_take.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 14:51:32 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*right_fork(t_philo *philo)
{
	return (&philo->forks[philo->id]);
}

t_fork	*left_fork(t_philo *philo)
{
	return (&philo->forks[(philo->id + 1) % philo->shared->philos_nbr]);
}

int	try_take_fork(t_fork *fork, t_philo *philo, int side)
{
	if (pthread_mutex_lock(&fork->mutex))
		return (print_err("try_take_fork: mutex lock failed"));
	if (fork->state == available)
	{
		fork->state = locked;
		philo->owned_forks[side] = 1;
		print_timestamp("has taken a fork", philo);
	}
	if (pthread_mutex_unlock(&fork->mutex))
		return (print_err("try_take_fork: mutex unlock failed"));
	return (0);
}

static int	release_fork(t_fork *fork, int *owned)
{
	if (pthread_mutex_lock(&fork->mutex))
		return (print_err("release_fork: mutex lock failed"));
	fork->state = available;
	*owned = 0;
	if (pthread_mutex_unlock(&fork->mutex))
		return (print_err("release_fork: mutex unlock failed"));
	return (0);
}

int	release_forks(t_philo *philo)
{
	if (release_fork(right_fork(philo), &philo->owned_forks[0]) == ERROR)
		return (ERROR);
	if (release_fork(left_fork(philo), &philo->owned_forks[1]) == ERROR)
		return (ERROR);
	return (0);
}

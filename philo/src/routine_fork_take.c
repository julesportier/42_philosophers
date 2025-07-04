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

void	try_take_fork(t_fork *fork, t_philo *philo, int side)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->state == available)
	{
		fork->state = locked;
		philo->owned_forks[side] = 1;
		print_timestamp("has taken a fork", philo);
	}
	pthread_mutex_unlock(&fork->mutex);
}

static void	release_fork(t_fork *fork, int *owned)
{
	pthread_mutex_lock(&fork->mutex);
	fork->state = available;
	*owned = 0;
	pthread_mutex_unlock(&fork->mutex);
}

void	release_forks(t_philo *philo)
{
	release_fork(right_fork(philo), &philo->owned_forks[0]);
	release_fork(left_fork(philo), &philo->owned_forks[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork_take.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/06/30 15:00:58 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#if (DEBUG && DBG_FORK)
	#include <stdio.h>
#endif

t_fork	*right_fork(t_philo *philo)
{
	return (&philo->forks[philo->id]);
}

t_fork	*left_fork(t_philo *philo)
{
	return (&philo->forks[(philo->id + 1) % philo->shared->philos_nbr]);
}

int	try_take_fork(t_fork *fork, int *owned)
{
	if (pthread_mutex_lock(&fork->mutex))
	{
#if (DEBUG && DBG_FORK)
		printf("try_take_fork mutex == %p\n", &fork->mutex);
#endif
		return (print_err("try_take_fork: mutex lock failed"));
	}
	if (fork->state == available)
	{
		fork->state = locked;
		*owned = 1;
	}
	if (pthread_mutex_unlock(&fork->mutex))
		return (print_err("try_take_fork: mutex unlock failed"));
	return (0);
}

// int	try_take_forks(t_fork *first_fork, t_fork *second_fork)
// {
// 	if (try_take_fork(first_fork) == ERROR)
// 		return (ERROR);
// 	if (try_take_fork(second_fork) == ERROR)
// 		return (ERROR);
// 	return (0);
// }

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

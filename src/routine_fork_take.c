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

static int	take_fork(t_fork *fork)
{
	if (pthread_mutex_lock(&fork->mutex))
		return (print_err("try_take_fork: mutex lock failed"));
	if (fork->state == available)
		fork->state = locked;
	if (pthread_mutex_unlock(&fork->mutex))
		return (print_err("try_take_fork: mutex unlock failed"));
	return (0);
}

int	take_forks(t_fork *first_fork, t_fork *second_fork)
{
	if (take_fork(first_fork) == ERROR)
		return (ERROR);
	if (take_fork(second_fork) == ERROR)
		return (ERROR);
	return (0);
}

static int	release_fork(t_fork *fork)
{
	if (pthread_mutex_lock(&fork->mutex))
		return (print_err("release_fork: mutex lock failed"));
	fork->state = available;
	if (pthread_mutex_unlock(&fork->mutex))
		return (print_err("release_fork: mutex unlock failed"));
	return (0);
}

int	release_forks(t_fork *first_fork, t_fork *second_fork)
{
	if (release_fork(first_fork) == ERROR)
		return (ERROR);
	if (release_fork(second_fork) == ERROR)
		return (ERROR);
	return (0);
}

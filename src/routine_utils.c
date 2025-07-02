/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 11:27:47 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#if (DEBUG && DBG_ROUTINE)
	#include <stdio.h>
#endif

// static int	eats_first(t_philo *philo)
// {
// 	int	philos_nbr;
//
// 	philos_nbr = philo->shared->philos_nbr;
// 	if (philo->id + 1 != philos_nbr && philo->id % 2 == 0)
// 		return (1);
// 	else
// 		return (0);
// }

int	set_death(t_death *death, t_philo *philo)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(&death->mutex))
		return (print_err("set_death: mutex lock failed"));
	if (death->state == alive)
	{
		death->state = dead;
		if (print_timestamp("died", philo) == ERROR)
			ret = ERROR;
	}
	if (pthread_mutex_unlock(&death->mutex))
		return (print_err("set_death: mutex unlock failed"));
	return (ret);
}

int	death_happened(t_death *death)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(&death->mutex))
		return (print_err("death_happened: mutex lock failed"));
	if (death->state == dead)
		ret = 1;
	if (pthread_mutex_unlock(&death->mutex))
		return (print_err("death_happened: mutex unlock failed"));
	return (ret);
}

int	reached_time(unsigned long long start_time, int time)
{
	if ((int)get_elapsed_time_ms(start_time) >= time)
		return (1);
	else
		return (0);
}

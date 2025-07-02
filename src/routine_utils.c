/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 14:45:53 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_even(int i)
{
	if (i % 2 == 0)
		return (1);
	else
		return (0);
}

int	set_death(t_death *death, t_philo *philo)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(&death->mutex))
		return (print_err("set_death: mutex lock failed\n"));
	if (death->state == alive)
	{
		print_death_timestamp(philo);
		death->state = dead;
	}
	if (pthread_mutex_unlock(&death->mutex))
		return (print_err("set_death: mutex unlock failed\n"));
	return (ret);
}

int	death_happened(t_death *death)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(&death->mutex))
		return (print_err("death_happened: mutex lock failed\n"));
	if (death->state == dead)
		ret = 1;
	if (pthread_mutex_unlock(&death->mutex))
		return (print_err("death_happened: mutex unlock failed\n"));
	return (ret);
}

int	reached_time(unsigned long long start_time, int time)
{
	if ((int)get_elapsed_time_ms(start_time) >= time)
		return (1);
	else
		return (0);
}

int	eaten_enough_meals(t_philo *philo)
{
	if (philo->shared->meals_nbr != UNSET
		&& philo->meals_taken >= philo->shared->meals_nbr)
	{
		return (1);
	}
	else
		return (0);
}

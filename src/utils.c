/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/06/30 12:03:45 by juportie         ###   ########.fr       */
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

int	calc_last_philo(int first, int philos_nbr)
{
	return ((first + philos_nbr - 1) % (philos_nbr));
}

int	is_last_philo(t_philo *philo)
{
	if (philo->id == calc_last_philo(
			philo->first_philo,
			philo->settings->number_of_philosophers))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

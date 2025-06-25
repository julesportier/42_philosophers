/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/06/30 11:09:40 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int get_right_fork(int philo_id)
{
	return (philo_id);
}

static int get_left_fork(int philo_id, int philos_nbr)
{
	return ((philo_id + 1) % philos_nbr);
}

int calc_first_fork(int philo_id, int philos_nbr)
{
	if (is_even(philo_id))
 		return (get_left_fork(philo_id, philos_nbr));
	else
 		return (get_right_fork(philo_id));
}

int calc_second_fork(int philo_id, int philos_nbr)
{
	if (is_even(philo_id))
 		return (get_right_fork(philo_id));
	else
 		return (get_left_fork(philo_id, philos_nbr));
}

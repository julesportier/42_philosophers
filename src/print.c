/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/06/30 12:03:03 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	print_timestamp(char *str, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->shared->printf_mutex))
		return (print_err("print_timestamp: mutex lock failed"));
	printf(
		"%llu %d %s\n",
		get_elapsed_time_ms(philo->shared->start_time),
		philo->id + 1,
		str
	);
	(void)str;
	if (pthread_mutex_unlock(&philo->shared->printf_mutex))
		return (print_err("print_timestamp: mutex unlock failed"));
	return (0);
}

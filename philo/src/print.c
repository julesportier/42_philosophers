/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/09 10:56:56 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
		++len;
	return (len);
}

int	print_err(char *str)
{
	write(2, str, ft_strlen(str));
	return (ERROR);
}

void	print_timestamp(char *str, t_philo *philo)
{
	if (philo->parameters->sim.state == running)
	{
		printf(
			"%llu %d %s\n",
			get_elapsed_time_ms(philo->parameters->start_time),
			philo->id + 1,
			str);
	}
}

void	print_timestamp_locked(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->parameters->sim.mutex);
	print_timestamp(str, philo);
	pthread_mutex_unlock(&philo->parameters->sim.mutex);
}

void	print_death_timestamp(t_philo *philo)
{
	printf(
		"%llu %d died\n",
		get_elapsed_time_ms(philo->parameters->start_time),
		philo->id + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:20:52 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 13:28:59 by juportie         ###   ########.fr       */
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

int	print_timestamp(char *str, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->shared->death.mutex))
		return (print_err("print_timestamp: mutex lock failed\n"));
	if (philo->shared->death.state == alive)
	{
		printf(
			"%llu %d %s\n",
			get_elapsed_time_ms(philo->shared->start_time),
			philo->id + 1,
			str);
	}
	if (pthread_mutex_unlock(&philo->shared->death.mutex))
		return (print_err("print_timestamp: mutex unlock failed\n"));
	return (0);
}

void	print_death_timestamp(t_philo *philo)
{
	printf(
		"%llu %d is dead\n",
		get_elapsed_time_ms(philo->shared->start_time),
		philo->id + 1);
}

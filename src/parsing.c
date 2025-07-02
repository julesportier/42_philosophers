/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:34:16 by juportie          #+#    #+#             */
/*   Updated: 2025/06/30 10:18:39 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	overflows(int nbr_n, int nbr_n1)
{
	int mul;

	if (nbr_n != 0)
	{
		mul = nbr_n * 10;
		if (nbr_n != mul / 10)
			return (1);
		if (mul > 2147483647 - nbr_n1)
			return (1);
	}
	return (0);
}

static int	arg_to_int(char *nptr)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (print_err(
					"argument must contain only positive numbers"));
		if (overflows(nbr, nptr[i] - '0'))
			return (print_err("argument number is too big"));
		nbr = nbr * 10 + (nptr[i] - '0');
		++i;
	}
	return (nbr);
}

static int	init_shared_mutexes(t_shared *shared)
{
	if (pthread_mutex_init(&shared->death.mutex, NULL))
		return (ERROR);
	if (pthread_mutex_init(&shared->printf_mutex, NULL))
	{
		pthread_mutex_destroy(&shared->death.mutex);
		return (ERROR);
	}
	shared->death.state = alive;
	if (pthread_mutex_init(&shared->block_mutex, NULL))
	{
		pthread_mutex_destroy(&shared->death.mutex);
		pthread_mutex_destroy(&shared->printf_mutex);
		return (ERROR);
	}
	return (0);
}

int	init_shared(t_shared *shared, int argc, char *argv[])
{
	shared->philos_nbr = arg_to_int(argv[1]);
	if (shared->philos_nbr == ERROR)
		return (ERROR);
	shared->time_to_die = arg_to_int(argv[2]);
	if (shared->time_to_die == ERROR)
		return (ERROR);
	shared->time_to_eat = arg_to_int(argv[3]);
	if (shared->time_to_eat == ERROR)
		return (ERROR);
	shared->time_to_sleep = arg_to_int(argv[4]);
	if (shared->time_to_sleep == ERROR)
		return (ERROR);
	if (argc == 6)
		shared->meals_nbr = arg_to_int(argv[5]);
	else
		shared->meals_nbr = UNSET;
	if (shared->meals_nbr == ERROR)
		return (ERROR);
	shared->start_time = 0;// THIS IS SET AGAIN AT SIMULATION START
	if (init_shared_mutexes(shared) == ERROR)
		return (ERROR);
	return (0);
}

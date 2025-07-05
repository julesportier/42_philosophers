/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:34:16 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 13:29:50 by juportie         ###   ########.fr       */
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
	int	mul;

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
					"philo: argument must contain only positive numbers\n"));
		if (overflows(nbr, nptr[i] - '0'))
			return (print_err(
					"philo: "
					"argument must contain only numbers under 2147483647\n"));
		nbr = nbr * 10 + (nptr[i] - '0');
		++i;
	}
	return (nbr);
}

static int	init_shared_mutexes(t_shared *shared)
{
	shared->sim.state = running;
	shared->sim.philos_done = 0;
	if (pthread_mutex_init(&shared->sim.mutex, NULL))
		return (print_err("init_shared_mutexes: mutex init failure\n"));
	return (0);
}

int	init_shared(t_shared *shared, int argc, char *argv[])
{
	shared->philos_nbr = arg_to_int(argv[1]);
	if (shared->philos_nbr == ERROR)
		return (ERROR);
	if (shared->philos_nbr > 1000)
		return (print_err("philo: maximum nbr of philos is 1000\n"));
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
	if (init_shared_mutexes(shared) == ERROR)
		return (ERROR);
	return (0);
}

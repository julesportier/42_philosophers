/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:13:55 by juportie          #+#    #+#             */
/*   Updated: 2025/06/23 11:36:51 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef DEBUG
#  define DEBUG 1
# endif

typedef struct s_settings
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosophers_must_eat;
}	t_settings;

// error.c
int	print_err(char *msg);
// arg_to_int.c
int	arg_to_int(char *nptr);

#endif

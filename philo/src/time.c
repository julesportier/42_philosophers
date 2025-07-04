/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:36:04 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 14:42:44 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

unsigned long long	get_time(void)
{
	struct timeval		tv;
	unsigned long long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_usec + (tv.tv_sec * 1000000);
	return (time);
}

unsigned long long	get_elapsed_time_ms(unsigned long long ref)
{
	unsigned long long	time;

	time = get_time();
	time = time - ref;
	time = time / 1000;
	return (time);
}

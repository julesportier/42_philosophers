/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:36:04 by juportie          #+#    #+#             */
/*   Updated: 2025/06/24 14:37:12 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>

#if (DEBUG && DBG_TIME)
	#include <stdio.h>
#endif

unsigned long long	get_time()
{
	struct timeval		tv;
	unsigned long long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_usec + (tv.tv_sec * 1000000);
	return (time);
}

unsigned long long	get_elapsed_time_us(unsigned long long ref)
{
	unsigned long long	time;

	time = get_time();
	time = time - ref;

#if (DEBUG && DBG_TIME)
	printf("elapsed time us == %llu\n", time);
#endif

	return (time);
}

unsigned long long	get_elapsed_time_ms(unsigned long long ref)
{
	unsigned long long	time;

	time = get_time();
	time = time - ref;
	time = time / 1000;

#if (DEBUG && DBG_TIME)
	printf("elapsed time ms == %llu\n", time);
#endif

	return (time);
}

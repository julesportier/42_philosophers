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

unsigned long long	get_time()
{
	struct timeval		tv;
	unsigned long long	time;

	gettimeofday(&tv, NULL);
	if (DEBUG && DBG_TIME)
	{
		printf("%ld\n", tv.tv_sec);
		printf("%ld\n", tv.tv_usec);
	}
	time = tv.tv_usec + (tv.tv_sec * 1000000);
	if (DEBUG && DBG_TIME)
		printf("%llu\n", time);
	return (time);
}

unsigned long long	get_elapsed_time(unsigned long long *ref)
{
	unsigned long long	time;

	time = get_time();
	time = time - *ref;
	if (DEBUG && DBG_TIME)
		printf("elapsed time == %llu\n", time);
	return (time);
}

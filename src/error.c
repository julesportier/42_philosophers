/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:11:35 by juportie          #+#    #+#             */
/*   Updated: 2025/06/23 11:30:01 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

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

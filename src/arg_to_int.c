/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:21:53 by juportie          #+#    #+#             */
/*   Updated: 2025/06/23 09:29:58 by juportie         ###   ########.fr       */
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

// static int	mul_overflow(int a, int b)
// {
// 	int result;
//
// 	if (a != 0 && b != 0)
// 	{
// 		result = a * b;
// 		if (a != result / b)
// 			return (1);
// 	}
// 	return (0);
// }

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

int	arg_to_int(char *nptr)
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

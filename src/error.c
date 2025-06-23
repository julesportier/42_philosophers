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

#include <stdlib.h>
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

// void	putstr_fd(char *str, int fd)
// {
// 	int	len;
//
// 	len = ft_strlen(str);
// 	write(fd, str, len);
// }

int	print_err(char *str)
{
	char	*error_prefix;
	int		error_prefix_len;
	char	*msg;
	int		len;
	int		i;

	error_prefix = "philo: error: ";
	error_prefix_len = ft_strlen(error_prefix);
	len = error_prefix_len + ft_strlen(str) + 1;
	msg = malloc((len + 1) * sizeof(char));
	if (!msg)
		return (-1);
	i = -1;
	while (error_prefix[++i])
		msg[i] = error_prefix[i];
	i = -1;
	while (str[++i])
		msg[i + error_prefix_len] = str[i];
	msg[i + error_prefix_len] = '\n';
	msg[++i + error_prefix_len] = '\0';
	write(2, msg, len);
	free(msg);
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:13:04 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/24 18:10:54 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long int	safe_atoi(char *str)
{
	int						i;
	unsigned long long int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+')
			return (0);
		i++;
	}
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - '0';
	if (nb > 2147483647)
		return (0);
	return (nb);
}

long int	actual_time(void)
{
	struct timeval	tv;
	int				err;

	err = gettimeofday(&tv, NULL);
	if (err != 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

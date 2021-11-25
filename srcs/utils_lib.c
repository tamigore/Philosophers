/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:13:04 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/25 15:17:44 by tamigore         ###   ########.fr       */
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

void	fill_buf(char *buf, int time, int id, char *act)
{
	int	i;
	int	j;
	int	tmp;
	int	nb;

	i = 0;
	buf[i++] = 't';
	buf[i++] = 'i';
	buf[i++] = 'm';
	buf[i++] = 'e';
	buf[i++] = ' ';
	buf[i++] = '|';
	j = 0;
	nb = time;
	while (nb > 0)
	{
		j++;
		nb /= 10;
	}
	tmp = j;
	while (j >= 0)
	{
		buf[i + j--] = time % 10 + '0';
		time /= 10;
	}
	i += tmp;
	buf[i++] = '|';
	buf[i++] = ':';
	buf[i++] = ' ';
	buf[i++] = 'P';
	buf[i++] = 'h';
	buf[i++] = 'i';
	buf[i++] = 'l';
	buf[i++] = 'o';
	buf[i++] = 's';
	buf[i++] = 'o';
	buf[i++] = 'p';
	buf[i++] = 'h';
	buf[i++] = 'e';
	buf[i++] = ' ';
	buf[i++] = 'n';
	buf[i++] = 'u';
	buf[i++] = 'm';
	buf[i++] = 'b';
	buf[i++] = 'e';
	buf[i++] = 'r';
	buf[i++] = ' ';
	j = 0;
	nb = id;
	while (nb > 0)
	{
		j++;
		nb /= 10;
	}
	tmp = j;
	while (j >= 0)
	{
		buf[i + j--] = id % 10 + '0';
		id /= 10;
	}
	i += tmp;
	buf[i++] = ' ';
	j = 0;
	while (act[j])
		buf[i++] = act[j++];
	buf[i] = '\n';
}

void	print_buf(char *buf)
{
	int	i;
	int	j;

	i = 0;
	while (buf[i])
		i++;
	write(1, buf, i);
	j = 0;
	while (j < i)
		buf[j++] = '\0';
}

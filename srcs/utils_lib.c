/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:13:04 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/26 17:33:53 by tamigore         ###   ########.fr       */
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

void	ft_usleep(/*t_philo *philo, */long int time_in_ms)
{
	long int	start_time;

	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms/* && !check_death(philo)*/)
		usleep(time_in_ms / (time_in_ms / 2));
}

int	putnbr_to_buf(int nb, char *buf, int i)
{
	int	tmp;
	int	j;

	if (nb < 10)
	{
		buf[i] = nb + '0';
		return (1);
	}
	j = 0;
	tmp = nb;
	while (tmp > 0)
	{
		j++;
		tmp /= 10;
	}
	tmp = j;
	while (j > 0)
	{
		buf[i + --j] = nb % 10 + '0';
		nb /= 10;
	}
	return (tmp);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

int	fill_buf(char *str, int time, int id, char *buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '*')
		buf[i++] = str[j++];
	i += putnbr_to_buf(time, buf, i);
	j++;
	while (str[j] && str[j] != '*')
			buf[i++] = str[j++];
	i += putnbr_to_buf(id, buf, i);
	buf[i++] = ' ';
	return (i);
}

void	print_buf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
		i++;
	write(1, buf, i);
}

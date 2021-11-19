/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/19 16:55:24 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->arg.max)
	{
		printf("philo : nb = %d | eat = %d\n", env->philo[i].id, env->philo[i].eat);
		i++;
	}
}

unsigned long long int	safe_atoi(char *str)
{
	int						i;
	unsigned long long int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+')
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - '0';
	return (nb);
}

int	timestamp(struct timeval tv, int time, int nb, char *act)
{
	int err;
	int t;

	err = gettimeofday(&tv, NULL);
	if (err != 0)
		return (0);
	t = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - time;
    if (nb > 0)
	    printf("\x1b[31m""time |%d|""\x1b[36m"": Philosophe number %d %s\n", t, nb, act);
    else
        printf("\x1b[31m""time |%d|""\x1b[36m"": %s\n", t, act);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/23 20:10:04 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_close_fork(t_philo *philo)
{
	if (philo->fork.data)
	{
		if (philo->next_fork)
		{
			if (philo->next_fork->data)
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

long int	actual_time(void)
{
	struct timeval tv;
	int err;

	err = gettimeofday(&tv, NULL);
	if (err != 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_philo(t_env *env)
{
	int	i;

	i = 0;
	printf("arg : max = %d | time to die = %d | time to sleep = %d | time to eat = %d\n",\
		env->arg.nb, env->arg.t_die, env->arg.t_sleep, env->arg.t_eat);
	while (i < env->arg.nb)
	{
		printf("philo : nb = %d | eat = %d | last eat = %d | fork = %d", env->philo[i].id,\
		env->philo[i].eat, env->philo[i].last_eat.data, env->philo[i].fork.data);
		if (env->philo[i].next_fork)
			printf(" | next_fork = %d\n", env->philo[i].next_fork->data);
		else
			printf(" | only one fork\n");
		i++;
	}
}

int	timestamp(long int time, int nb, char *act)
{
	long int err;
	int t;

	err = actual_time();
	if (err == -1)
		return (0);
	t = err - time;
    if (nb > 0)
	    printf("\x1b[31m""time |%d|""\x1b[36m"": Philosophe number %d %s\n", t, nb, act);
    else
	{
        printf("\x1b[31m""time |%d|""\x1b[36m"": %s\n", t, act);
	}
	return (1);
}

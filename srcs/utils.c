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

void	*is_dead(void *param)
{
	t_philo	*philo;

	philo = param;
	while (!philo->arg.dead.data)
	{
//		printf("debug : full = %d | last_eat = %d | time to die = %d\n", philo->full, philo->last_eat, philo->arg.die);
		if (!philo->full && philo->last_eat > philo->arg.t_die)
		{
			pthread_mutex_lock(&(philo->arg.dead.mutex));
			philo->arg.dead.data = 1;
			pthread_mutex_unlock(&(philo->arg.dead.mutex));
			pthread_mutex_lock(&(philo->arg.print.mutex));
			philo->arg.print.f(philo->arg.tv, philo->arg.time, philo->id, "is dead");
			pthread_mutex_unlock(&(philo->arg.print.mutex));
		}
		printf("dafuk\n");
	}
	return (NULL);
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
		env->philo[i].eat, env->philo[i].last_eat, env->philo[i].fork.data);
		if (env->philo[i].next_fork)
			printf(" | next_fork = %d\n", env->philo[i].next_fork->data);
		else
			printf("\n");
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
	{
        printf("\x1b[31m""time |%d|""\x1b[36m"": %s\n", t, act);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:56:02 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/19 16:59:50 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_env *env, int	nb)
{
	int	ret;

	env->philo[nb].id = nb + 1;
	env->philo[nb].eat = 0;
	env->philo[nb].full = 0;
	ret = pthread_mutex_init(&(env->philo[nb].fork.mutex), NULL);
	if (ret != 0)
		return (0);
	env->philo[nb].fork.data = 1;
	return (1);
}

int	init_arg(t_env *env, char **av, int ac)
{
	int	ret;

	env->arg.max = safe_atoi(av[1]);
	env->arg.die = safe_atoi(av[2]);
	env->arg.sleep = safe_atoi(av[3]);
	env->arg.eat = safe_atoi(av[4]);
	if (ac == 6)
		env->arg.limit = safe_atoi(av[5]);
	else
		env->arg.limit = -1;
	gettimeofday(&env->arg.tv, NULL);
	env->arg.time = env->arg.tv.tv_sec * 1000 + env->arg.tv.tv_usec / 1000;
	ret = pthread_mutex_init(&(env->arg.dead.mutex), NULL);
	if (ret != 0)
		return (0);
	env->arg.dead.data = 0;
	ret = pthread_mutex_init(&(env->arg.print.mutex), NULL);
	if (ret != 0)
		return (0);
	env->arg.print.f = timestamp;
	return (1);
}

int		pars(t_env *env, char **av, int ac)
{
	int		i;
	int		ret;

	env->philo = NULL;
	ret = init_arg(env, av, ac);
	if (!ret)
	{
		printf("arg ?\n");
		return (0);
	}
	env->philo = malloc(sizeof(t_philo) * env->arg.max);
	if (!env->philo)
	{
		printf("malloc philo ?\n");
		return (0);
	}
	i = 0;
	while (i < env->arg.max)
	{
		ret = init_philo(env, i);
		if (!ret)
		{
			printf("init philo ?\n");
			return (0);
		}
		if (i > 0)
			env->philo[i - 1].next_fork = &(env->philo[i].fork);
		i++;
	}
	if (i > 0)
		env->philo[i - 1].next_fork = &(env->philo[0].fork);
	return (1);
}

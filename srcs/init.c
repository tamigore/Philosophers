/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:56:02 by tamigore          #+#    #+#             */
/*   Updated: 2021/12/02 12:32:11 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_env *env, int nb)
{
	int	ret;

	env->philo[nb].id = nb + 1;
	env->philo[nb].eat = 0;
	ret = pthread_mutex_init(&(env->philo[nb].fork.mutex), NULL);
	if (ret != 0)
		return (0);
	env->philo[nb].fork.data = 1;
	env->philo[nb].arg = env->arg;
	ret = pthread_mutex_init(&(env->philo[nb].last_eat.mutex), NULL);
	if (ret != 0)
		return (0);
	env->philo[nb].last_eat.data = 0;
	ret = pthread_mutex_init(&(env->philo[nb].full.mutex), NULL);
	if (ret != 0)
		return (0);
	env->philo[nb].full.data = 0;
	return (1);
}

int	init_arg(t_env *env, char **av, int ac)
{
	int	ret;

	env->arg = malloc(sizeof(t_arg));
	if (!env->arg)
		return (0);
	env->arg->nb = safe_atoi(av[1]);
	env->arg->t_die = safe_atoi(av[2]);
	env->arg->t_eat = safe_atoi(av[3]);
	env->arg->t_sleep = safe_atoi(av[4]);
	if (!env->arg->t_die || !env->arg->nb || !env->arg->t_sleep \
		|| !env->arg->t_eat)
		return (0);
	if (ac == 6)
		env->arg->max_eat = safe_atoi(av[5]);
	else
		env->arg->max_eat = -1;
	ret = pthread_mutex_init(&(env->arg->dead.mutex), NULL);
	if (ret != 0)
		return (0);
	env->arg->dead.data = 0;
	ret = pthread_mutex_init(&(env->arg->print.mutex), NULL);
	if (ret != 0)
		return (0);
	env->arg->print.f = timestamp;
	return (1);
}

int	pars(t_env *env, char **av, int ac)
{
	int		i;
	int		ret;

	env->philo = NULL;
	ret = init_arg(env, av, ac);
	if (!ret)
		return (0);
	env->philo = malloc(sizeof(t_philo) * env->arg->nb);
	if (!env->philo)
		return (0);
	i = -1;
	while (++i < env->arg->nb)
	{
		ret = init_philo(env, i);
		if (!ret)
			return (0);
		if (i > 0 && env->arg->nb > 1)
			env->philo[i - 1].next_fork = &(env->philo[i].fork);
	}
	if (i > 0 && env->arg->nb > 1)
		env->philo[i - 1].next_fork = &(env->philo[0].fork);
	else
		env->philo[i - 1].next_fork = NULL;
	return (1);
}

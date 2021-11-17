/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:56:02 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/17 18:59:18 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int	nb)
{
	t_philo philo;

	philo.nb = nb;
	philo.eat = 0;
	philo.full = 0;
	return (philo);
}

t_env	pars(char **av, int ac)
{
	t_env	env;
	int		i;

	env.max = safe_atoi(av[1]);
	env.die = safe_atoi(av[2]);
	env.sleep = safe_atoi(av[3]);
	env.eat = safe_atoi(av[4]);
	if (ac == 6)
		env.limit = safe_atoi(av[5]);
	else
		env.limit = -1;
	i = 0;
	while (i < env.max)
	{
		env.fork[i].data = 1;
		pthread_mutex_init(&(env.fork[i].mutex), NULL);
		env.philo[i] = init_philo(i + 1);
		i++;
	}
	env.dead.data = 0;
	pthread_mutex_init(&(env.dead.mutex), NULL);
	env.print.f = timestamp;
	pthread_mutex_init(&(env.print.mutex), NULL);
	gettimeofday(&env.tv, NULL);
	env.time = env.tv.tv_sec * 1000 + env.tv.tv_usec / 1000;
	return (env);
}

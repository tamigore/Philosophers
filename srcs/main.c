/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:31:08 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/30 14:14:41 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->arg->nb)
	{
		pthread_mutex_destroy(&(env->philo[i].fork.mutex));
		pthread_mutex_destroy(&(env->philo[i].full.mutex));
		pthread_mutex_destroy(&(env->philo[i].last_eat.mutex));
		i++;
	}
	pthread_mutex_destroy(&(env->arg->print.mutex));
	pthread_mutex_destroy(&(env->arg->dead.mutex));
	if (env->philo)
		free(env->philo);
	if (env->arg)
		free(env->arg);
}

int	main(int ac, char **av)
{
	t_env	env;

	if (ac < 5 || ac > 6)
	{
		printf("Usage :./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]");
		exit(EXIT_FAILURE);
	}
	if (!pars(&env, av, ac))
	{
		if (env.philo)
			free(env.philo);
		if (env.arg)
			free(env.arg);
		return (0);
	}
	start(&env);
	finish(&env);
	return (1);
}

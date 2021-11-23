/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:31:08 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/23 17:05:02 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->arg.nb)
	{
		pthread_mutex_destroy(&(env->philo[i].fork.mutex));
		i++;
	}
	free(env->philo);
	pthread_mutex_destroy(&(env->arg.print.mutex));
	pthread_mutex_destroy(&(env->arg.dead.mutex));
}

int		main(int ac, char **av)
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
		printf("pars error\n");
		if (env.philo)
			free(env.philo);
		return (0);
	}
	printf("The %d Philosophers are now sitted around the table\n", env.arg.nb);
	print_philo(&env);
	start(&env);
	finish(&env);
	return (1);
}

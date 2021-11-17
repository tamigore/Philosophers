/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:31:08 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/17 19:21:24 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//int	get_close_fork(t_env *env)
//{
//	
//}

void	*routine(void *arg)
{
	t_env *env;

	env = arg;
	if (env->philo[env->index].full != 1)
	{
//		if (env->fork[env->index] && get_close_fork(env))
//		{
//			
//		}
		if (env->limit != -1)
		{
			if (env->philo[env->index].eat < env->limit)
				env->philo[env->index].eat++;
			else
				env->philo[env->index].full = 1;
		}
		else
			env->philo[env->index].eat++;
		pthread_mutex_lock(&(env->print.mutex));
		env->print.f(env->tv, env->time, env->philo[env->index].nb, "is eating");
		pthread_mutex_unlock(&(env->print.mutex));
	}
	return (NULL);
}

void	start(t_env *env)
{
	int err;
	int	i;

	i = 0;
	timestamp(env->tv, env->time, 0, "start");
	while (i < env->max)
	{
		env->index = i;
		err = pthread_create(&(env->philo[i].thread), NULL, routine, env);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < env->max)
		pthread_join(env->philo[i++].thread, NULL);
}

void	finish(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->max)
	{
		pthread_mutex_destroy(&(env->fork[i].mutex));
		i++;
	}
	pthread_mutex_destroy(&(env->print.mutex));
	pthread_mutex_destroy(&(env->dead.mutex));
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
	env = pars(av, ac);
	printf("The %d Philosophers are now sitted around the table\n", env.max);
	print_philo(env);
	start(&env);
	finish(&env);
	return (0);
}

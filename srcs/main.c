/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:31:08 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/19 16:58:07 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	get_close_fork(t_philo *philo)
// {
// 	if (philo.fork.data)
// 	{
// 		if (philo.fork.next_fork->data)
// 			return (1);
// 	}
// 	return (0);
// }

// void	*routine(void *arg)
// {
// 	t_philo	*philo;
// 	int		close;

// 	philo = arg;
// 	while (philo.full != 1)
// 	{
// 		close = get_close_fork(philo);
// 		if (env->fork[env->index].data == 1 && close > -1)
// 		{
// 			pthread_mutex_lock(&(env->fork[close].mutex));
// 			env->fork[close].data = 0;
// 			pthread_mutex_lock(&(env->fork[env->index].mutex));
// 			env->fork[env->index].data = 2;
// 			pthread_mutex_lock(&(env->print.mutex));
// 			env->print.f(env->tv, env->time, env->philo[env->index].nb, "has taken a fork");
// 			pthread_mutex_unlock(&(env->print.mutex));
// 			if (env->limit != -1)
// 			{
// 				if (env->philo[env->index].eat < env->limit)
// 					env->philo[env->index].eat++;
// 				else
// 					env->philo[env->index].full = 1;
// 			}
// 			if (env->fork[env->index].data == 2)
// 			{
// 				pthread_mutex_lock(&(env->print.mutex));
// 				env->print.f(env->tv, env->time, env->philo[env->index].nb, "is eating");
// 				pthread_mutex_unlock(&(env->print.mutex));
// 				usleep(env->eat);
// 			}
// 			env->fork[close].data = 1;
// 			pthread_mutex_unlock(&(env->fork[close].mutex));
// 			env->fork[env->index].data = 1;
// 			pthread_mutex_unlock(&(env->fork[env->index].mutex));
// 			pthread_mutex_lock(&(env->print.mutex));
// 			env->print.f(env->tv, env->time, env->philo[env->index].nb, "is sleeping");
// 			pthread_mutex_unlock(&(env->print.mutex));
// 			usleep(env->sleep);
// 			pthread_mutex_lock(&(env->print.mutex));
// 			env->print.f(env->tv, env->time, env->philo[env->index].nb, "is thinking");
// 			pthread_mutex_unlock(&(env->print.mutex));
// 		}
// 		printf("NULL\n");
// 	}
// 	return (NULL);
// }

// void	start(t_env *env)
// {
// 	int err;
// 	int	i;

// 	i = 0;
// 	timestamp(env->arg.tv, env->arg.time, 0, "start");
// 	while (i < env->arg.max)
// 	{
// 		if (env->philo[i].id % 2 == 0)
// 			usleep(10);
// 		err = pthread_create(&(env->philo[i].thread), NULL, routine, env);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < env->arg.max)
// 		pthread_join(env->philo[i++].thread, NULL);
// }

void	finish(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->arg.max)
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
		printf("why ?\n");
		if (env.philo)
			free(env.philo);
		return (0);
	}
	printf("The %d Philosophers are now sitted around the table\n", env.arg.max);
	print_philo(&env);
//	start(&env);
	finish(&env);
	return (1);
}

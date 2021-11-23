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
			return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->full != 1 && !philo->arg.dead.data)
	{
		if (philo->arg.dead.data == 1)
			break ;
		if (philo->fork.data == 1 && get_close_fork(philo))
		{
			pthread_mutex_lock(&(philo->next_fork->mutex));
			philo->fork.data = 0;
			pthread_mutex_lock(&(philo->fork.mutex));
			philo->fork.data = 2;
			pthread_mutex_lock(&(philo->arg.print.mutex));
			philo->arg.print.f(philo->arg.tv, philo->arg.time, philo->id, "has taken a fork");
			pthread_mutex_unlock(&(philo->arg.print.mutex));
			pthread_mutex_lock(&(philo->arg.print.mutex));
			philo->arg.print.f(philo->arg.tv, philo->arg.time, philo->id, "is eating");
			pthread_mutex_unlock(&(philo->arg.print.mutex));
			philo->last_eat = (philo->arg.tv.tv_sec * 1000 + philo->arg.tv.tv_usec / 1000) - philo->arg.time - philo->last_eat;
			usleep(philo->arg.t_eat);
			philo->next_fork->data = 1;
			pthread_mutex_unlock(&(philo->next_fork->mutex));
			philo->fork.data = 1;
			pthread_mutex_unlock(&(philo->fork.mutex));
			pthread_mutex_lock(&(philo->arg.print.mutex));
			philo->arg.print.f(philo->arg.tv, philo->arg.time, philo->id, "is sleeping");
			pthread_mutex_unlock(&(philo->arg.print.mutex));
			usleep(philo->arg.t_sleep);
			pthread_mutex_lock(&(philo->arg.print.mutex));
			philo->arg.print.f(philo->arg.tv, philo->arg.time, philo->id, "is thinking");
			pthread_mutex_unlock(&(philo->arg.print.mutex));
			if (philo->arg.max_eat != -1)
			{
				if (philo->eat < philo->arg.max_eat - 1)
					philo->eat++;
				else
					philo->full = 1;
			}
		}
	}
	return (NULL);
}

void	start(t_env *env)
{
	int err;
	int	i;

	i = 0;
	timestamp(env->arg.tv, env->arg.time, 0, "start");
	while (i < env->arg.nb)
	{
		if (env->philo[i].id % 2 == 0)
			usleep(10);
		err = pthread_create(&(env->philo[i].thread), NULL, routine, &(env->philo[i]));
		if (err != 0)
		{
			printf("bug in pthread create thread\n");
			return ;
		}
		err = pthread_create(&(env->philo[i].death), NULL, is_dead, &(env->philo[i]));
		if (err != 0)
		{
			printf("bug in pthread create dead\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < env->arg.nb)
		pthread_join(env->philo[i++].thread, NULL);
}

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
		printf("why ?\n");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:06:05 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/26 17:56:17 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 1;
	while (!check_death(philo) && !check_full(philo))
	{
		pthread_mutex_lock(&(philo->fork.mutex));
		if (philo->next_fork)
			pthread_mutex_lock(&(philo->next_fork->mutex));
		i = (philo->fork.data == 1 && get_close_fork(philo));
		if (i && !check_death(philo))
			act_eat(philo);
		pthread_mutex_unlock(&(philo->fork.mutex));
		if (philo->next_fork)
			pthread_mutex_unlock(&(philo->next_fork->mutex));
		act_other(philo, i);
	}
	return (NULL);
}

int	start(t_env *env)
{
	int	i;
	int	time;
	int	full;

	i = -1;
	env->arg->time = actual_time();
	while (++i < env->arg->nb)
	{
		pthread_create(&(env->philo[i].thread), NULL, routine, \
			&(env->philo[i]));
	}
	full = 0;
	while (!check_death(env->philo))
	{
		i = 0;
		while (i < env->arg->nb)
		{
			time = actual_time() - env->arg->time;
			pthread_mutex_lock(&(env->philo[i].last_eat.mutex));
			time = time - env->philo[i].last_eat.data > env->arg->t_die;
			pthread_mutex_unlock(&(env->philo[i].last_eat.mutex));
			if (time && !check_death(&env->philo[i]) && !check_full(&env->philo[i]))
			{
				pthread_mutex_lock(&(env->arg->dead.mutex));
				env->arg->dead.data = 1;
				pthread_mutex_unlock(&(env->arg->dead.mutex));
				pthread_mutex_lock(&(env->arg->print.mutex));
				env->arg->print.f(&env->philo[i], 0, "is dead");
				pthread_mutex_unlock(&(env->arg->print.mutex));
				i = env->arg->nb - 1;
			}
			if (check_full(&env->philo[i]))
			{
				full++;
				if (full == env->arg->nb)
				{
					pthread_mutex_lock(&(env->arg->dead.mutex));
					env->arg->dead.data = 1;
					pthread_mutex_unlock(&(env->arg->dead.mutex));
					i = env->arg->nb - 1;
				}
			}
			i++;
		}
	}
	i = 0;
	while (i < env->arg->nb)
		pthread_join(env->philo[i++].thread, NULL);
	ft_usleep(100);
	return (1);
}

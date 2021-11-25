/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:06:05 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/25 14:00:19 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_dead(void *param)
{
	t_philo		*philo;
	long int	time;

	philo = (t_philo *)param;
	while (!check_death(philo) && !check_full(philo))
	{
		time = actual_time() - philo->arg->time;
		pthread_mutex_lock(&(philo->last_eat.mutex));
		time = time - philo->last_eat.data > philo->arg->t_die;
		pthread_mutex_unlock(&(philo->last_eat.mutex));
		if (time && !check_death(philo) && !check_full(philo))
		{
			pthread_mutex_lock(&(philo->arg->dead.mutex));
			philo->arg->dead.data = 1;
			pthread_mutex_unlock(&(philo->arg->dead.mutex));
			pthread_mutex_lock(&(philo->arg->print.mutex));
			philo->arg->print.f(philo, 0, "is dead");
			pthread_mutex_unlock(&(philo->arg->print.mutex));
			return (NULL);
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 1;
	while (!check_death(philo) && !check_full(philo))
	{
		if (philo->id % 2 == 1)
		{
			pthread_mutex_lock(&(philo->fork.mutex));
			if (philo->next_fork)
				pthread_mutex_lock(&(philo->next_fork->mutex));
			i = (philo->fork.data == 1 && get_close_fork(philo));
			pthread_mutex_unlock(&(philo->fork.mutex));
			if (philo->next_fork)
				pthread_mutex_unlock(&(philo->next_fork->mutex));
			if (i && !check_death(philo))
				act_eat(philo);
			act_other(philo, i);
		}
		else
		{
			act_other(philo, i);
			pthread_mutex_lock(&(philo->fork.mutex));
			if (philo->next_fork)
				pthread_mutex_lock(&(philo->next_fork->mutex));
			i = (philo->fork.data == 1 && get_close_fork(philo));
			pthread_mutex_unlock(&(philo->fork.mutex));
			if (philo->next_fork)
				pthread_mutex_unlock(&(philo->next_fork->mutex));
			if (i)
				act_eat(philo);
		}
	}
	return (NULL);
}

int	start(t_env *env)
{
	int	err;
	int	i;

	i = -1;
	timestamp(env->philo, 0, "start");
	while (++i < env->arg->nb)
	{
		err = pthread_create(&(env->philo[i].thread), NULL, routine, \
			&(env->philo[i]));
		if (err != 0)
			return (0);
		err = pthread_create(&(env->arg->death), NULL, is_dead, \
			&(env->philo[i]));
		if (err != 0)
			return (0);
	}
	i = 0;
	while (i < env->arg->nb)
	{
		pthread_join(env->arg->death, NULL);
		pthread_join(env->philo[i++].thread, NULL);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:06:05 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/24 11:48:09 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(philo->arg.dead.mutex));
	if (philo->arg.dead.data == 1)
		ret = 1;
	pthread_mutex_unlock(&(philo->arg.dead.mutex));
	return (ret);
}

void	*is_dead(void *param)
{
	t_philo		*philo;
	long int	time;

	philo = (t_philo *)param;
	while (1)
	{
		ft_usleep(5);
		if (check_death(philo))
			return (NULL);
		time = actual_time() - philo->arg.time;
		pthread_mutex_lock(&(philo->last_eat.mutex));
		if (time - philo->last_eat.data > philo->arg.t_die && !check_death(philo))
		{
			pthread_mutex_unlock(&(philo->last_eat.mutex));
			pthread_mutex_lock(&(philo->arg.print.mutex));
			philo->arg.print.f(philo->arg.time, philo->id, "is dead");
			pthread_mutex_unlock(&(philo->arg.print.mutex));
			pthread_mutex_lock(&(philo->arg.dead.mutex));
			philo->arg.dead.data = 1;
			pthread_mutex_unlock(&(philo->arg.dead.mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->last_eat.mutex));
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		if (check_death(philo))
			return (NULL);
		else
		{
			pthread_mutex_lock(&(philo->fork.mutex));
			if (philo->next_fork)
				pthread_mutex_lock(&(philo->next_fork->mutex));
			if (philo->fork.data == 1 && get_close_fork(philo) && !check_death(philo))
			{
				i = 1;
				philo->fork.data = 0;
				philo->fork.data = 2;
				pthread_mutex_lock(&(philo->arg.print.mutex));
				philo->arg.print.f(philo->arg.time, philo->id, "has taken a fork");
				philo->arg.print.f(philo->arg.time, philo->id, "is eating");
				pthread_mutex_unlock(&(philo->arg.print.mutex));
				pthread_mutex_lock(&(philo->last_eat.mutex));
				philo->last_eat.data = actual_time() - philo->arg.time - philo->last_eat.data;
				pthread_mutex_unlock(&(philo->last_eat.mutex));
				ft_usleep(philo->arg.t_eat);
				philo->next_fork->data = 1;
				philo->fork.data = 1;
				if (philo->arg.max_eat != -1)
				{
					if (philo->eat < philo->arg.max_eat - 1)
						philo->eat++;
					else
						return (NULL);
				}
			}
			pthread_mutex_unlock(&(philo->fork.mutex));
			if (philo->next_fork)
				pthread_mutex_unlock(&(philo->next_fork->mutex));
			if (i == 1 && !check_death(philo))
			{
				pthread_mutex_lock(&(philo->arg.print.mutex));
				philo->arg.print.f(philo->arg.time, philo->id, "is sleeping");
				pthread_mutex_unlock(&(philo->arg.print.mutex));
				ft_usleep(philo->arg.t_sleep);
			}
			if (i == 1 && !check_death(philo))
			{
				pthread_mutex_lock(&(philo->arg.print.mutex));
				philo->arg.print.f(philo->arg.time, philo->id, "is thinking");
				pthread_mutex_unlock(&(philo->arg.print.mutex));
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
	timestamp(env->arg.time, 0, "start");
	while (i < env->arg.nb)
	{
		if (env->philo[i].id % 2 == 0)
			ft_usleep(10);
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
	{
		pthread_join(env->philo[i].thread, NULL);
		pthread_join(env->philo[i].death, NULL);
		i++;
	}
}
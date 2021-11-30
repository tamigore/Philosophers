/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:44:16 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/30 17:02:00 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	act_other(t_philo *philo, int i)
{
	if (i == 2 && !check_death(philo))
	{
		pthread_mutex_lock(&(philo->arg->print.mutex));
		philo->arg->print.f(philo, 1, "is sleeping");
		pthread_mutex_unlock(&(philo->arg->print.mutex));
		ft_usleep(philo->arg->t_sleep);
	}
	if (i == 2 && !check_death(philo))
	{
		pthread_mutex_lock(&(philo->arg->print.mutex));
		philo->arg->print.f(philo, 1, "is thinking");
		pthread_mutex_unlock(&(philo->arg->print.mutex));
	}
}

void	check_eat(t_philo *philo)
{
	if (philo->arg->max_eat != -1)
	{
		if (philo->eat < philo->arg->max_eat - 1)
			philo->eat++;
		else
		{
			pthread_mutex_lock(&(philo->full.mutex));
			philo->full.data = 1;
			pthread_mutex_unlock(&(philo->full.mutex));
		}
	}
}

static void	extra_fork(t_philo *philo, int x, int y)
{
	if (philo->next_fork)
	{
		pthread_mutex_lock(&(philo->fork.mutex));
		philo->fork.data = x;
		pthread_mutex_unlock(&(philo->fork.mutex));
		pthread_mutex_lock(&(philo->next_fork->mutex));
		philo->next_fork->data = y;
		pthread_mutex_unlock(&(philo->next_fork->mutex));
	}
}

void	act_eat(t_philo *philo)
{
	extra_fork(philo, 2, 0);
	pthread_mutex_lock(&(philo->arg->print.mutex));
	philo->arg->print.f(philo, 1, "has taken a fork");
	philo->arg->print.f(philo, 1, "is eating");
	pthread_mutex_unlock(&(philo->arg->print.mutex));
	pthread_mutex_lock(&(philo->last_eat.mutex));
	philo->last_eat.data = actual_time() - philo->arg->time;
	pthread_mutex_unlock(&(philo->last_eat.mutex));
	ft_usleep(philo->arg->t_eat);
	extra_fork(philo, 1, 1);
}

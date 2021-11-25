/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:44:16 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/25 15:06:06 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	act_other(t_philo *philo, int i)
{
	if (i)
	{
		pthread_mutex_lock(&(philo->arg->print.mutex));
		philo->arg->print.f(philo, 1, "is sleeping");
		pthread_mutex_unlock(&(philo->arg->print.mutex));
		ft_usleep(philo->arg->t_sleep);
	}
	if (i)
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

void	act_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork.mutex));
	if (philo->next_fork)
		pthread_mutex_lock(&(philo->next_fork->mutex));
	philo->fork.data = 0;
	philo->fork.data = 2;
	pthread_mutex_lock(&(philo->arg->print.mutex));
	philo->arg->print.f(philo, 1, "has taken a fork");
	philo->arg->print.f(philo, 1, "is eating");
	pthread_mutex_unlock(&(philo->arg->print.mutex));
	pthread_mutex_lock(&(philo->last_eat.mutex));
	philo->last_eat.data = actual_time() - philo->arg->time;
	pthread_mutex_unlock(&(philo->last_eat.mutex));
	ft_usleep(philo->arg->t_eat);
	philo->next_fork->data = 1;
	philo->fork.data = 1;
	pthread_mutex_unlock(&(philo->fork.mutex));
	if (philo->next_fork)
		pthread_mutex_unlock(&(philo->next_fork->mutex));
	check_eat(philo);
}

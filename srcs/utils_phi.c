/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/30 17:00:41 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(philo->arg->dead.mutex));
	if (philo->arg->dead.data == 1)
		ret = 1;
	pthread_mutex_unlock(&(philo->arg->dead.mutex));
	return (ret);
}

int	check_full(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(philo->full.mutex));
	if (philo->full.data == 1)
		ret = 1;
	pthread_mutex_unlock(&(philo->full.mutex));
	return (ret);
}

int	get_close_fork(t_philo *philo)
{
	if (philo->next_fork)
	{
		if (philo->next_fork->data)
			return (1);
	}
	return (0);
}

int	timestamp(t_philo *philo, int nb, char *act)
{
	long int	err;
	int			t;

	if (!check_death(philo) || !nb)
	{
		err = actual_time();
		if (err == -1)
			return (0);
		t = err - philo->arg->time;
		printf("time |%d|: Phiosophe number %d %s\n", t, philo->id, act);
	}
	return (1);
}

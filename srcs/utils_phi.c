/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/25 15:16:18 by tamigore         ###   ########.fr       */
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
	if (philo->fork.data)
	{
		if (philo->next_fork)
		{
			if (philo->next_fork->data)
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	timestamp(t_philo *philo, int nb, char *act)
{
	long int	err;
	int			t;
	char		buf[128];

	if (!check_death(philo) || !nb)
	{
		err = actual_time();
		if (err == -1)
			return (0);
		t = err - philo->arg->time;
		fill_buf(buf, t, philo->id, act);
		print_buf(buf);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:30:56 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/24 18:49:32 by tamigore         ###   ########.fr       */
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

int	timestamp(long int time, int nb, char *act)
{
	long int	err;
	int			t;

	err = actual_time();
	if (err == -1)
		return (0);
	t = err - time;
	if (nb > 0)
	{
			printf("\x1b[31m""time |%5d|""\x1b[36m"": Philosophe number %d %s\n", \
			t, nb, act);	
	}
	else
	{
		printf("\x1b[31m""time |%d|""\x1b[36m"": %s\n", t, act);
	}
	return (1);
}

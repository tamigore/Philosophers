/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:06:05 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/30 16:03:47 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (!check_death(philo) && !check_full(philo))
	{
		i = 0;
		if (philo->next_fork)
		{
			pthread_mutex_lock(&(philo->fork.mutex));
			i = philo->fork.data == 1;
			pthread_mutex_unlock(&(philo->fork.mutex));
			pthread_mutex_lock(&(philo->next_fork->mutex));
			i += get_close_fork(philo);
			pthread_mutex_unlock(&(philo->next_fork->mutex));
		}
		if (i == 2 && !check_death(philo))
		{
			act_eat(philo);
			check_eat(philo);
		}
		act_other(philo, i);
	}
	return (NULL);
}

static void	extra_full(t_env *env, int *full, int *i)
{
	(*full)++;
	if (*full == env->arg->nb)
	{
		pthread_mutex_lock(&(env->arg->dead.mutex));
		env->arg->dead.data = 1;
		pthread_mutex_unlock(&(env->arg->dead.mutex));
		*i = env->arg->nb - 1;
	}
}

static void	death_loop(t_env *env, int i, int time, int full)
{
	while (i < env->arg->nb)
	{
		pthread_mutex_lock(&(env->philo[i].last_eat.mutex));
		time = actual_time() - env->arg->time - env->philo[i].last_eat.data > \
			env->arg->t_die;
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
			extra_full(env, &full, &i);
		i++;
	}
}

int	start(t_env *env)
{
	int	i;
	int	time;
	int	full;

	i = -1;
	env->arg->time = actual_time();
	while (++i < env->arg->nb)
		pthread_create(&(env->philo[i].thread), NULL, routine, \
			&(env->philo[i]));
	full = 0;
	time = 0;
	while (!check_death(env->philo))
		death_loop(env, 0, time, full);
	i = 0;
	while (i < env->arg->nb)
		pthread_join(env->philo[i++].thread, NULL);
	ft_usleep(100);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:20:04 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/04 18:20:05 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_all(t_env *env, int ex)
{
	t_philo	*tmp;

	if (env)
	{
		while (env->philo)
		{
			tmp = env->philo;
			env->philo = env->philo->next;
			free(tmp);
		}
		free(env);
	}
	exit(ex);
}

static t_env	*pars(int ac, char **av)
{
	t_env	*env;
	t_philo	*tmp;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		exit_all(NULL, EXIT_FAILURE);
	env->max = ft_atoi(av[1]);
	if (env->max < 2)
	{
		ft_putstr("Usage : ./philo : nb_of_philosophers time_to_die time_eat");
		ft_putstr(" time_to_sleep [nb_of_times_each_philosopher_must_eat]\n");
		exit_all(env, EXIT_FAILURE);
	}
	i = 0;
	env->philo = malloc(sizeof(t_philo);
	if (!env->philo)
		exit_all(env, EXIT_FAILURE);
	tmp = env->philo;
	env->philo = env->philo->next;
	while (i < env->max - 1)
	{
		env->philo = malloc(sizeof(t_philo);
		if (!env->philo)
			exit_all(env, EXIT_FAILURE);
		env->philo = env->philo->next;
	}
	tmp->philo->next = NULL;
}

int	main(int ac, char **av)
{
	t_env	*env;

	if (ac < 5 || ac > 6)
	env = pars(ac, av);
	return (0);
}

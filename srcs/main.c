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

void	exit_all(t_philo  *philo, int ex)
{
	t_philo	*tmp;

	if (!philo)
		exit(ex);
	while (philo)
	{
		tmp = philo;
		philo = philo->next;
		free(tmp);
	}
	exit(ex);
}

void			timestamp(int time, char *act)
{
	printf("time_stamp_in_ms %d %s\n", time, act);
}

static t_philo	*init_philo(int	nb, t_env *env)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo) * nb);
	if (!philo)
		return (NULL);
	philo->nb = nb;
	philo->eat = 0;
	philo->fork = 0;
	philo->next = NULL;
	philo->env = env;
	return (philo);
}

static t_env	pars(char **av)
{
	t_env	env;
	t_philo	*philo;
	int		i;

	env.max = ft_atoi(av[1]);
	ft_putstr("Error\n");
	if (!env.max)
		exit_all(NULL, EXIT_FAILURE);
	i = 1;
	philo = init_philo(i++, &env);
	ft_putstr("Error 2\n");
	if (!philo)
		exit_all(philo, EXIT_FAILURE);
	env.philo = philo;
	ft_putstr("Error 3\n");
	philo = philo->next;
	while (i <= env.max)
	{
		printf("Error i = %d\n", i);
		philo = init_philo(i, &env);
		if (!philo)
			exit_all(env.philo, EXIT_FAILURE);
		philo = philo->next;
		i++;
	}
	philo = env.philo;
	return (env);
}

void	print_philo(t_philo *philo)
{
	if (!philo)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	printf("philo : nb = %d | eat = %d | fork = %d | next = %p\n", philo->nb, philo->eat, philo->fork);
	philo = philo->next;
	ft_putstr("Error\n");
	while (philo->nb != 1)
	{
		printf("philo : nb = %d | eat = %d | fork = %d\n", philo->nb, philo->eat, philo->fork);
		philo = philo->next;
	}
}

int		main(int ac, char **av)
{
	t_env	env;

	if (ac < 5 || ac > 6)
	{
		printf("Usage :./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]");
		exit(EXIT_FAILURE);
	}
	env = pars(av);
	print_philo(env.philo);
	return (0);
}

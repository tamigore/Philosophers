/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:20:11 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/04 18:20:16 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_eat
{
	int		fork;
	int		time;
}	t_eat;

typedef struct s_sleep
{
	int		time;
}	t_sleep;

typedef struct s_think
{
	int		time;
}	t_think;

typedef struct s_philo
{
	int             nb;
	struct s_eat    eat;
	struct s_sleep  sleep;
	struct s_think  think;
	struct s_philo	*next;
}	t_philo;

typedef struct s_env
{
	int				max;
	int             *fork;
	struct s_philo	*philo;
}	t_env;

#endif

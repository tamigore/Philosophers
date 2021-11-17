/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:20:11 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/17 19:08:12 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_mutex
{
	int				data;
	pthread_mutex_t	mutex;
}	t_mutex;

typedef struct s_print
{
	int				(* f)(struct timeval tv, int timestart, int nb, char *act);
	pthread_mutex_t	mutex;
}	t_print;

typedef struct s_philo
{
	int             nb;
	int				eat;
	int				full;
	pthread_t		thread;
}	t_philo;

typedef struct s_env
{
	int				max;
	int				die;
	int				sleep;
	int			    eat;
	int				limit;
	int				index;
	int				time;
	struct timeval	tv;
	struct s_mutex	dead;
	struct s_print	print;
	struct s_mutex	fork[200];
	struct s_philo	philo[200];
}	t_env;

unsigned long long int	safe_atoi(char *str);
void					print_philo(t_env env);
int						timestamp(struct timeval tv, int time, int nb, char *act);

t_env			pars(char **av, int ac);
t_philo			init_philo(int	nb);

#endif

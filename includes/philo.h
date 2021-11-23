/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:20:11 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/19 16:58:36 by tamigore         ###   ########.fr       */
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

typedef struct s_arg
{
	int				nb;
	int				t_die;
	int				t_sleep;
	int			    t_eat;
	int				max_eat;
	int				time;
	struct timeval	tv;
	struct s_mutex	dead;
	struct s_print	print;
}	t_arg;

typedef struct s_philo
{
	int             id;
	int				eat;
	int				full;
	int				last_eat;
	struct s_mutex	fork;
	struct s_mutex	*next_fork;
	struct s_arg	arg;
	pthread_t		thread;
	pthread_t		death;
}	t_philo;

typedef struct s_env
{
	struct s_philo	*philo;
	struct s_arg	arg;
}	t_env;

unsigned long long int	safe_atoi(char *str);
void					print_philo(t_env *env);
int						timestamp(struct timeval tv, int time, int nb, char *act);
void					*is_dead(void *param);

int				pars(t_env *env, char **av, int ac);
int				init_philo(t_env *env, int	nb);

#endif

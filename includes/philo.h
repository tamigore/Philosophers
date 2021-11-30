/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:20:11 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/26 17:51:18 by tamigore         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				eat;
	struct s_mutex	full;
	struct s_mutex	last_eat;
	struct s_mutex	fork;
	struct s_mutex	*next_fork;
	struct s_arg	*arg;
	pthread_t		thread;
}	t_philo;

typedef struct s_print
{
	int				(*f)(struct s_philo *philo, int nb, char *act);
	pthread_mutex_t	mutex;
}	t_print;

typedef struct s_arg
{
	int				nb;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				max_eat;
	long int		time;
	struct s_mutex	dead;
	struct s_print	print;
	pthread_t		death;
}	t_arg;

typedef struct s_env
{
	struct s_philo	*philo;
	struct s_arg	*arg;
}	t_env;

void					ft_putstr(char *str);

int						check_death(t_philo *philo);
int						check_full(t_philo *philo);
void					print_philo(t_env *env);
int						get_close_fork(t_philo *philo);
int						timestamp(t_philo *philo, int nb, char *act);

long int				actual_time(void);
void					ft_usleep(long int time_in_ms);
unsigned long long int	safe_atoi(char *str);
void					print_buf(char *buf);
int						fill_buf(char *str, int time, int id, char *buf);

void					*routine(void *arg);
int						start(t_env *env);

int						pars(t_env *env, char **av, int ac);
int						init_philo(t_env *env, int nb);

void					act_other(t_philo *philo, int i);
void					act_eat(t_philo *philo);

#endif

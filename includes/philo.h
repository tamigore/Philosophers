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
# include <stdio.h>
# include "libft.h"

typedef struct s_philo
{
	int             nb;
	int				eat;
	int				fork;
}	t_philo;

typedef struct s_env
{
	int				max;
	int				die;
	int				sleep;
	int			    eat;
	int				think;
	int             *fork;
	struct s_philo	*philo;
}	t_env;

#endif

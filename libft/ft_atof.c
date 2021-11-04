/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:37:29 by tamigore          #+#    #+#             */
/*   Updated: 2021/11/04 13:37:31 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long int	get_int(char *str, long long int *res)
{
	int						i;
	int						neg;
	unsigned long long int	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while ((str[i] <= '\r' && str[i] >= '\t') || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - '0';
	*res = nb * neg;
	return (i);
}

double	ft_atof(char *str)
{
	int				i;
	double			nb;
	long long int	fract;
	long long int	inter;

	i = 0;
	nb = 0;
	fract = 0;
	inter = 0;
	i = get_int(&str[i], &inter);
	if (str[i] == '.')
	{
		i++;
		i = get_int(&str[i], &fract);
		nb = (double)fract;
		while (nb >= 1)
			nb /= 10;
	}
	nb += (double)inter;
	if (str[0] == '-' && nb > 0)
		nb *= -1;
	return (nb);
}

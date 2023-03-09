/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 22:16:31 by kkaczoro          #+#    #+#             */
/*   Updated: 2022/03/16 18:31:55 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char chr);
static int	ft_isdigit(int c);
static int	ft_nbdigit(char *s);

int	ft_atoi(const char *nptr)
{
	int		nb;
	int		sign;
	char	*str;

	nb = 0;
	sign = 1;
	str = (char *)nptr;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str) || (sign == -1
			&& ft_nbdigit(str) > 19))
		return (0);
	else if (ft_nbdigit(str) > 19)
		return (-1);
	while (ft_isdigit(*str))
		nb = nb * 10 + *str++ - '0';
	return (sign * nb);
}

static int	ft_isspace(char chr)
{
	if (chr == ' ' || chr == '\f' || chr == '\n'
		|| chr == '\r' || chr == '\t' || chr == '\v')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static int	ft_nbdigit(char *s)
{
	int	nb;

	nb = 0;
	while (s[nb] && ft_isdigit(s[nb]))
		nb++;
	return (nb);
}

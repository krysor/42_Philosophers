/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:06:13 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/02/28 15:23:06 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *pnt)
{
	t_vars	*vars;

	vars = (t_vars *)pnt;
	printf("im a philo but idk which one\n");
	
	while (!vars->dead)
	{
		vars->dead = 1;
	}
	return (NULL);
}

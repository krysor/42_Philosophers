/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:06:13 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/01 17:54:00 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *pnt)
{
	t_philo	*philo;

	philo = (t_philo *)pnt;
	printf("im a philo nb %d\n", philo->i + 1);
	// while (!philo->vars->dead)
	// {
	// 	philo->vars->dead = 1;
	// }
	return (NULL);
}

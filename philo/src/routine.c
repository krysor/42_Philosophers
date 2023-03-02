/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:06:13 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/02 12:51:11 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *pnt)
{
	t_philo	*philo;

	philo = (t_philo *)pnt;
	printf("im a philo nb %d\n", philo->i + 1);
	
	while (1)
	{
		pthread_mutex_lock(&philo->vars->mtx);
		if (philo->vars->dead == 0)
			philo->vars->dead = 1;
		else
		{
			pthread_mutex_unlock(&philo->vars->mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->vars->mtx);
	}

	return (NULL);
}

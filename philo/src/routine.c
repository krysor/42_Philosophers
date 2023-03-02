/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:06:13 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/02 13:11:43 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_alive(t_vars *vars);

void	*routine(void *pnt)
{
	t_philo	*philo;

	philo = (t_philo *)pnt;

	while (all_philos_alive(philo->vars))
	{
		printf("im a philo nb %d\n", philo->i + 1);
		
		
		
		
		if (philo->i == 2)
		{
			pthread_mutex_lock(&philo->vars->mutex);
			philo->vars->dead = 1;
			pthread_mutex_unlock(&philo->vars->mutex);
		}
	}
	return (NULL);
}

static int	all_philos_alive(t_vars *vars)
{
	int	result;
	
	result = 1;
	pthread_mutex_lock(&vars->mutex);
	if (vars->dead == 1)
		result = 0;
	pthread_mutex_unlock(&vars->mutex);
	return (result);
}

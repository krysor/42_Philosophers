/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:11:41 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/01 11:22:22 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_new(int i, t_vars *vars, void *(*routine)(void *))
{
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->vars = vars;
	philo->odd = i % 2;
	if (pthread_create(&philo->thread, NULL, routine, philo)
		|| pthread_mutex_init(&philo->fork_right, NULL))
	{
		pthread_join(philo->thread);
		pthread_mutex_destroy(philo->mutex);
		free(philo);
		return (NULL);
	}
	return (philo);
}

int	philo_add(t_philo *philos, t_philo *new)
{
	t_philo	*temp;

	if (!new)
		return (1);
	if (!philos)
	{
		philos = new;
		return (0);
	}	
	temp = philos;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->fork_left = &temp->fork_right;
	philos->fork_left = &temp->fork_right;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:11:41 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/01 12:00:50 by kkaczoro         ###   ########.fr       */
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
		pthread_join(philo->thread, NULL);
		pthread_mutex_destroy(&philo->fork_right);
		free(philo);
		return (NULL);
	}
	return (philo);
}

int	philo_add(void *philos, t_philo *new)
{
	t_philo	*philo;
	t_philo	*temp;

	if (!new)
		return (1);
	philo = (t_philo *)philos;
	if (!philo)
	{
		philo = new;
		return (0);
	}	
	temp = philo;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->fork_left = &temp->fork_right;
	philo->fork_left = &temp->fork_right;
	return (0);
}

int	philo_free_all(t_philo *philo)
{
	t_philo *temp;
	
	while (philo)
	{
		temp = philo->next;
		pthread_join(philo->thread, NULL);
		pthread_mutex_destroy(&philo->fork_right);
		free(philo);
		philo = temp;
	}
	return (1);
}

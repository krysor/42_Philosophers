/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:11:41 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/02 12:57:53 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_new(int i, t_vars *vars, void *(*routine)(void *))
{
	t_philo	*philo;

	philo = &vars->philos[i];
	philo->vars = vars;
	philo->i = i;
	if (pthread_mutex_init(&philo->fork_left, NULL)
		|| pthread_create(&philo->thread, NULL, routine, &vars->philos[i]))
	{
		pthread_join(philo->thread, NULL);
		pthread_mutex_destroy(&philo->fork_left);
		return (1);
	}
	return (0);
}

int	philo_free_all(t_vars *vars)
{
	int	i;
	
	i = 0;
	while (i < vars->nb_philos)
	{
		pthread_join(vars->philos[i].thread, NULL);
		pthread_mutex_destroy(&vars->philos[i].fork_left);
		i++;
	}
	free(vars->philos);
	pthread_mutex_destroy(&vars->mutex);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:11:41 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/05 16:02:49 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_new(int i, t_vars *vars, void *(*routine)(void *))
{
	t_philo	*philo;
	int		index;
	//char	color[6];
	
	philo = &vars->philos[i];
	philo->vars = vars;
	philo->i = i;
	
	index = -1;
	while (++index < 6)
		philo->color[index] = RED[index];
	philo->color[3] = '1' + (philo->i % 7); 
	
	if (vars->argc == 6)
		philo->nb_times_to_eat = vars->nb_times_to_eat;
	if (pthread_mutex_init(&philo->fork_left, NULL)
		|| pthread_create(&philo->thread, NULL, routine, &vars->philos[i])
		|| pthread_mutex_init(&philo->lock_time, NULL))//check if for sure here
	{
		pthread_join(philo->thread, NULL);
		pthread_mutex_destroy(&philo->fork_left);
		pthread_mutex_destroy(&philo->lock_time);//check if for sure here
		return (1);
	}
	return (0);
}

int	philo_free_all(t_vars *vars)
{
	int	i;
	
	i = -1;
	while (++i < vars->nb_philos)
		pthread_join(vars->philos[i].thread, NULL);
	i = -1;
	while (++i < vars->nb_philos)
	{
		pthread_mutex_destroy(&vars->philos[i].fork_left);
		pthread_mutex_destroy(&vars->philos[i].lock_time);
	}
	free(vars->philos);
	pthread_mutex_destroy(&vars->mutex);
	pthread_mutex_destroy(&vars->mutex2);
	pthread_mutex_destroy(&vars->mutex_print);
	return (1);
}

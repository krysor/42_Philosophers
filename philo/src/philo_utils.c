/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:11:41 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/01 17:22:48 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_new(int i, t_vars *vars, void *(*routine)(void *))
{
	t_philo	*philo;

	philo = &vars->philos[i];
	philo->vars = vars;
	philo->odd = i % 2;
	if (pthread_mutex_init(&philo->fork_left, NULL)
		|| pthread_create(&philo->thread, NULL, routine, &philo))
	{
		pthread_join(philo->thread, NULL);
		pthread_mutex_destroy(&philo->fork_left);
		return (1);
	}
	return (0);
}

// int	philo_add(t_vars *vars, t_philo *new)
// {
// 	t_philo	*temp;

// 	if (!new)
// 		return (1);
// 	if (!vars->philo_first)
// 	{
// 		vars->philo_first = new;
// 		return (0);
// 	}
// 	temp = vars->philo_first;
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new;
// 	new->fork_left = &temp->fork_right;
// 	vars->philo_first->fork_left = &temp->fork_right;
// 	return (0);
// }

int	philo_free_all(t_vars *vars)
{
	int	i;
	
	i = 0;
	while (i < vars->nb_philos)
	{
		printf("i: %d\n", i);
		pthread_join(vars->philos[i].thread, NULL);
		pthread_mutex_destroy(&vars->philos[i].fork_left);
		i++;
	}
	free(vars->philos);
	return (1);
}


// t_philo	*philo_new(int i, t_vars *vars, void *(*routine)(void *))
// {
// 	t_philo		*philo;

// 	philo = (t_philo *)malloc(sizeof(t_philo));
// 	if (!philo)
// 		return (NULL);
// 	philo->vars = vars;
// 	philo->odd = i % 2;
// 	if (pthread_mutex_init(&philo->fork_right, NULL)
// 		|| pthread_create(&philo->thread, NULL, routine, philo))
// 	{
// 		pthread_join(philo->thread, NULL);
// 		pthread_mutex_destroy(&philo->fork_right);
// 		free(philo);
// 		return (NULL);
// 	}
// 	return (philo);
// }

// int	philo_add(t_vars *vars, t_philo *new)
// {
// 	t_philo	*temp;

// 	if (!new)
// 		return (1);
// 	if (!vars->philo_first)
// 	{
// 		vars->philo_first = new;
// 		return (0);
// 	}
// 	temp = vars->philo_first;
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new;
// 	new->fork_left = &temp->fork_right;
// 	vars->philo_first->fork_left = &temp->fork_right;
// 	return (0);
// }

// int	philo_free_all(t_vars *vars)
// {
// 	t_philo *temp;
	
// 	temp = vars->philo_first;
// 	while (temp)
// 	{
// 		vars->philo_first = vars->philo_first->next;
// 		printf("wut1\n");
// 		//temp = vars->philo_first->next;
// 		printf("join: %d\n", pthread_join(temp->thread, NULL));
// 		printf("destroy: %d\n",pthread_mutex_destroy(&temp->fork_right));
// 		printf("wut2\n");
// 		free(temp);
// 		temp = vars->philo_first;
// 	}
// 	printf("executed or nah?3\n");
// 	return (1);
// }
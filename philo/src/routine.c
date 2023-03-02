/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:06:13 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/02 18:28:02 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo);
static int	all_philos_alive(t_vars *vars);
//static void	wait_until(struct timeval *time_start, suseconds_t interval);
// static void	wait_until(t_philo *philo, suseconds_t interval);

void	*routine(void *pnt)
{
	t_philo	*philo;

	philo = (t_philo *)pnt;
	if (philo->i % 2)
	{
		if (usleep(philo->vars->time_to_eat * 1000))
			return (NULL);
		philo->time_to_die -= philo->vars->time_to_eat;
	}
	while (all_philos_alive(philo->vars) && philo->time_to_die > 0)
	{
		if (eat(philo))
			return (NULL);

		//add death
			
		if (philo->vars->argc == 6 && !philo->nb_times_to_eat)
			return (NULL);
	}
	return (NULL);
}

static int	eat(t_philo *philo)
{
	int	i_philo_right;
	
	if (pthread_mutex_lock(&philo->fork_left))
		return (1);
	i_philo_right = philo->i + 1;
	if (i_philo_right == philo->vars->nb_philos)
		i_philo_right = 0;
	if (pthread_mutex_lock(&philo->vars->philos[i_philo_right].fork_left))
		return (1);
	printf("philo %d has eaten\n", philo->i + 1);//replace this with custom function
	philo->nb_times_to_eat--;
	philo->time_to_die = philo->vars->time_to_die;
	if (pthread_mutex_unlock(&philo->fork_left))
		return (1);
	if (pthread_mutex_unlock(&philo->vars->philos[i_philo_right].fork_left))
		return (1);
	return (0);
}

static int	all_philos_alive(t_vars *vars)
{
	int	result;
	
	result = 1;
	if (pthread_mutex_lock(&vars->mutex))
		return (0);
	if (vars->dead == 1)
		result = 0;
	if (pthread_mutex_unlock(&vars->mutex))
		return (0);
	return (result);
}

// //static void	wait_until(struct timeval *time_start, suseconds_t interval)
// static void	wait_until(t_philo *philo, suseconds_t interval)
// {
// 	struct timeval	time;
	
// 	struct timeval	time_start = philo->vars->time_start;

// 	if (gettimeofday(&time, NULL))
// 		return ;
// 	// while (time_start->tv_sec * 1000 + time_start->tv_usec + interval
// 		// < time.tv_sec * 1000 + time.tv_usec)
// 	//printf("time_start.tv_sec * 1000 + time_start.tv_usec: %d\n", time_start.tv_usec);
	
// 	while (time_start.tv_sec * 1000 + time_start.tv_usec
// 			>= time.tv_sec * 1000 + time.tv_usec - interval)
// 	{
// 		printf("philo nb %d waiting\n", philo->i + 1);
// 		usleep(50);
// 		gettimeofday(&time, NULL);
// 	}
// }

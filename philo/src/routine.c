/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:06:13 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/06 12:52:13 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo);
static void	wait_interval(struct timeval *time_start, suseconds_t interval);

void	*routine(void *pnt)
{
	t_philo	*philo;

	philo = (t_philo *)pnt;
	if (all_philos_alive(philo->vars) && philo->i % 2)
		wait_interval(&philo->vars->time_start,
			philo->vars->time_to_eat * 1000);
	while (all_philos_alive(philo->vars))
	{
		if (eat(philo))
			break ;
		print_message(philo, "is sleeping");
		wait_interval(&philo->time_last_meal,
			(philo->vars->time_to_eat + philo->vars->time_to_sleep) * 1000);
		print_message(philo, "is thinking");
	}
	return (NULL);
}

static int	eat(t_philo *philo)
{
	int	i_philo_right;

	pthread_mutex_lock(&philo->fork_left);
	print_message(philo, "has taken a fork");
	i_philo_right = philo->i + 1;
	if (i_philo_right == philo->vars->nb_philos)
		i_philo_right = 0;
	if (i_philo_right == philo->i)
		return (1);
	pthread_mutex_lock(&philo->vars->philos[i_philo_right].fork_left);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	if (gettimeofday(&philo->time_last_meal, NULL))
		return (1);
	philo->nb_times_to_eat--;
	if (philo->vars->argc == 6 && philo->nb_times_to_eat == 0)
	{
		pthread_mutex_lock(&philo->vars->mutex_nb_philos_to_finish);
		philo->vars->nb_philos_to_finish--;
		pthread_mutex_unlock(&philo->vars->mutex_nb_philos_to_finish);
	}
	wait_interval(&philo->time_last_meal, philo->vars->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->vars->philos[i_philo_right].fork_left);
	pthread_mutex_unlock(&philo->fork_left);
	return (0);
}

static void	wait_interval(struct timeval *time_start, suseconds_t interval)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return ;
	while (((time.tv_sec - time_start->tv_sec) * 1000000
			+ time.tv_usec - time_start->tv_usec) < interval)
	{
		usleep(100);
		if (gettimeofday(&time, NULL))
			return ;
	}
}

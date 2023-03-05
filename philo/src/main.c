/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:36:08 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/05 14:50:48 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_stop(t_vars *vars);
int		check_if_dead(t_vars *vars);
int		still_philos_to_finish(t_vars *vars);
int		set_philo_start_time(t_vars *vars);

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
		return (1);
	vars.argc = argc;
	if (init_vars(&vars, argv))
		return (2);
	if (gettimeofday(&vars.time_start, NULL)
		|| set_philo_start_time(&vars)
		|| pthread_mutex_unlock(&vars.mutex)
		|| pthread_mutex_unlock(&vars.mutex2))
		set_stop(&vars);
	while (all_philos_alive(&vars) && still_philos_to_finish(&vars))
	{
		if (check_if_dead(&vars))
			break ;
	}
	philo_free_all(&vars);
	//system("leaks philo");
	return (0);
}

int	set_philo_start_time(t_vars *vars)
{
	int	i;
	t_philo *philo;

	i = 0;
	while (i < vars->nb_philos)
	{
		philo = &vars->philos[i++];
		philo->time_last_meal.tv_sec = vars->time_start.tv_sec;
		philo->time_last_meal.tv_usec = vars->time_start.tv_usec;
	}
	return (0);
}

int	still_philos_to_finish(t_vars *vars)
{
	int	result;
	
	if (vars->argc != 6)
		return (1);
	result = 0;
	if (pthread_mutex_lock(&vars->mutex2))
		return (0);
	if (vars->nb_philos_to_finish)
		result = 1;
	if (pthread_mutex_unlock(&vars->mutex2))
		return (0);	
	return (result);
}

void	set_stop(t_vars *vars)
{
	pthread_mutex_lock(&vars->mutex);
	vars->stop = 1;
	pthread_mutex_unlock(&vars->mutex);
}

int	check_if_dead(t_vars *vars)
{
	int				i;
	struct timeval	time_now;
	struct timeval	interval;

	if (gettimeofday(&time_now, NULL))
		return (1);
	i = -1;
	while (++i < vars->nb_philos)
	{
		pthread_mutex_lock(&vars->philos[i].lock_time);
		set_time_difference(&interval, &(vars->philos[i].time_last_meal), &time_now);
		pthread_mutex_unlock(&vars->philos[i].lock_time);
		if (interval.tv_sec * 1000 + interval.tv_usec / 1000
			> vars->time_to_die)
		{
			print_message(&vars->philos[i], "died");
			set_stop(vars);
			return (1);
		}
	}
	return (0);
}

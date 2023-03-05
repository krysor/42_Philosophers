/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:36:08 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/05 13:50:05 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_stop(t_vars *vars);
int		check_if_dead(t_vars *vars);
int		still_philos_to_finish(t_vars *vars);

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
		return (1);
	vars.argc = argc;
	if (init_vars(&vars, argv))
		return (2);
	//if (gettimeofday(&vars.time_start, NULL) || pthread_mutex_unlock(&vars.mutex))//unlock unnecessary unless I go back to locking
	if (//gettimeofday(&vars.time_start, NULL)
		pthread_mutex_unlock(&vars.mutex)
		|| pthread_mutex_unlock(&vars.mutex2))//unlock unnecessary unless I go back to locking
		set_stop(&vars);
	//printf("before main_loop\n");
	while (all_philos_alive(&vars) && still_philos_to_finish(&vars))
	{
		//printf("main_loop\n");
		if (check_if_dead(&vars))
			break ;
	}
	//printf("after main_loop\n");
	philo_free_all(&vars);
	//system("leaks philo");
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
		// printf("%stime_last_meal.tv_sec: %ld\n", RESET, vars->philos[i].time_last_meal.tv_sec);
		// printf("%stime_now.tv_sec: %ld\n", RESET, time_now.tv_sec);
		// printf("%sinterval.tv_sec: %ld\n", RESET, interval.tv_sec);

		if (interval.tv_sec * 1000 + interval.tv_usec / 1000
			> vars->time_to_die)
		{
			//printf("here\n");
			
			set_stop(vars);
			print_message(&vars->philos[i], "died");
			return (1);
		}
	}
	return (0);
}

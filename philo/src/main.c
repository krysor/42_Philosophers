/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:36:08 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/04 14:27:11 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_stop(t_vars *vars);
int		check_if_dead(t_vars *vars);

int	main(int argc, char *argv[])
{
	t_vars	vars;

	//printf("%sargv[%d]: %d\n", RED, 1, ft_atoi(argv[1]));
	if (argc != 5 && argc != 6)
		return (1);
	vars.argc = argc;
	if (init_vars(&vars, argv))
		return (2);
	if (gettimeofday(&vars.time_start, NULL) || pthread_mutex_unlock(&vars.mutex))
		set_stop(&vars);
	//printf("%sAm I here?1\n", RESET);
	while (all_philos_alive(&vars) && vars.nb_philos_to_finish)
	{
		//printf("%sAm I here?2\n", RESET);
		if (check_if_dead(&vars))
			break ;
	}
	//printf("%sAm I here?3\n", RESET);
	philo_free_all(&vars);
	//system("leaks philo");
	return (0);
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
		//printf("%si: %d\n", RESET, i);
		set_time_difference(&interval, 
			&time_now, &(vars->philos[i].time_last_meal));
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

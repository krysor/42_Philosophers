/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:36:08 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/02 17:39:07 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_vars *vars);

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
		set_dead(&vars);
	philo_free_all(&vars);
	//system("leaks philo");
	return (0);
}

void	set_dead(t_vars *vars)
{
	pthread_mutex_lock(&vars->mutex);
	vars->dead = 1;
	pthread_mutex_unlock(&vars->mutex);
}
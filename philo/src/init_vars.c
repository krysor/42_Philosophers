/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:29 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/02/28 14:41:51 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_vars(t_vars *vars, int argc, char *argv[])
{
	int	i;
	
	vars->dead = 0;
	vars->nb_philos = ft_atoi(argv[NUMBER_OF_PHILOSOPHERS]);
	vars->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	vars->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	vars->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argc == 6)
		vars->nb_times_to_eat = ft_atoi(argv[NB_TIMES_EACH_PHILO_MUST_EAT]);
	if (vars->nb_philos < 0 || vars->time_to_die < 0 || vars->time_to_eat < 0
		|| vars->time_to_sleep < 0 || (argc == 6 && vars->nb_times_to_eat < 0))
		return (1);
	i = 0;
	while (i < vars->nb_philos)
	{
		if (pthread_create(&vars->buffer_philo[i], NULL, &routine, &vars)
			|| pthread_mutex_init(&vars->buffer_fork[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

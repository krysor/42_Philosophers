/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:29 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/04 14:20:09 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_vars(t_vars *vars, char *argv[])
{
	int	i;

	vars->nb_philos = ft_atoi(argv[NUMBER_OF_PHILOSOPHERS]);
	vars->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	vars->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	vars->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (vars->argc == 6)
		vars->nb_times_to_eat = ft_atoi(argv[NB_TIMES_EACH_PHILO_MUST_EAT]);
	vars->philos = malloc(sizeof(t_philo) * vars->nb_philos);
	if (!vars->philos || vars->nb_philos < 0 || vars->time_to_die < 0
		|| vars->time_to_eat < 0 || vars->time_to_sleep < 0 || 
		(vars->argc == 6 && vars->nb_times_to_eat < 0))
		return (1);
	vars->nb_philos_to_finish = vars->nb_philos;
	vars->stop = 0;
	if (pthread_mutex_init(&vars->mutex, NULL) || pthread_mutex_lock(&vars->mutex))//necessary or not?
		return (philo_free_all(vars));
	i = 0;
	while (i < vars->nb_philos)
	{
		if (philo_new(i++, vars, routine))
			return (philo_free_all(vars));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:29 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/02/28 12:16:15 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_vars(t_vars *vars, int argc, char *argv[])
{
	int	i;

	vars->nb_philos = ft_atoi(argv[NUMBER_OF_PHILOSOPHERS]);
	vars->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	vars->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	vars->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argc == 6)
		vars->nb_times_must_eat
			= ft_atoi(argv[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT]);
	i = 0;
	while (i < vars->nb_philos)
	{
		if (!pthread_create(&vars->buffer[i++], NULL, &routine, &vars))
			printf("pthread_create succeded\n");
		else
			printf("pthread_create failed\n");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:36:08 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/02/28 11:59:51 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_vars(t_vars *vars, char *argv[]);
void	clean_vars(t_vars *vars);

void	*routine(void *vars)
{
	(void)vars;
	printf("thread executed\n");
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	
	//printf("%sargv[%d]: %d\n", RED, 1, ft_atoi(argv[1]));
	if (argc != 5 && argc != 6)
		return (1);

	init_vars(&vars, argv);
	clean_vars(&vars);

	return (0);
}

void	init_vars(t_vars *vars, char *argv[])
{
	int	i;
	
	vars->nb_philos = ft_atoi(argv[NUMBER_OF_PHILOSOPHERS]);
	vars->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	vars->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	vars->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	vars->nb_times_must_eat = ft_atoi(argv[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT]);
	i = 0;
	while (i < vars->nb_philos)
	{
		if (!pthread_create(&vars->buffer[i++], NULL, &routine, &vars))
			printf("pthread_create succeded\n");
		else
			printf("pthread_create failed\n");
	}
}

void	clean_vars(t_vars *vars)
{
	int	i;
	
	i = 0;
	while (i < vars->nb_philos)
	{
		pthread_join(vars->buffer[i++], NULL);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:29 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/07 09:56:46 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_vars_atoi(t_vars *vars, char *argv[]);
static int	init_vars_mutex(t_vars *vars);
static int	philo_new(int i, t_vars *vars, void *(*routine)(void *));

int	init_vars(t_vars *vars, char *argv[])
{
	int	i;

	vars->stop = 0;
	if (init_vars_atoi(vars, argv))
		return (1);
	vars->philos = malloc(sizeof(t_philo) * vars->nb_philos);
	if (!vars->philos)
		return (1);
	if (init_vars_mutex(vars))
		return (clean_all(vars));
	i = 0;
	while (i < vars->nb_philos)
	{
		if (philo_new(i++, vars, routine))
			return (clean_all(vars));
	}
	return (0);
}

static int	init_vars_atoi(t_vars *vars, char *argv[])
{
	vars->nb_philos = ft_atoi(argv[NUMBER_OF_PHILOSOPHERS]);
	vars->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	vars->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	vars->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (vars->argc == 6)
	{
		vars->nb_times_to_eat = ft_atoi(argv[NB_TIMES_EACH_PHILO_MUST_EAT]);
		vars->nb_philos_to_finish = vars->nb_philos;
	}
	if (vars->nb_philos < 0 || vars->time_to_die < 0
		|| vars->time_to_eat < 0 || vars->time_to_sleep < 0
		|| (vars->argc == 6 && vars->nb_times_to_eat < 0))
		return (1);
	return (0);
}

static int	init_vars_mutex(t_vars *vars)
{
	if (pthread_mutex_init(&vars->mutex_stop, NULL)
		|| pthread_mutex_init(&vars->mutex_nb_philos_to_finish, NULL)
		|| pthread_mutex_init(&vars->mutex_print, NULL))
		return (1);
	pthread_mutex_lock(&vars->mutex_stop);
	return (0);
}

static int	philo_new(int i, t_vars *vars, void *(*routine)(void *))
{
	t_philo	*philo;
	int		index;

	philo = &vars->philos[i];
	philo->vars = vars;
	philo->i = i;
	index = -1;
	while (++index < 6)
		philo->color[index] = RED[index];
	philo->color[3] = '1' + (philo->i % 7);
	if (vars->argc == 6)
		philo->nb_times_to_eat = vars->nb_times_to_eat;
	if (pthread_create(&philo->thread, NULL, routine, &vars->philos[i])
		|| pthread_mutex_init(&philo->fork_left, NULL)
		|| pthread_mutex_init(&philo->mutex_time_last_meal, NULL))
		return (1);
	return (0);
}

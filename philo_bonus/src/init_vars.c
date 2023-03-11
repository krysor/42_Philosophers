/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:29 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/11 19:45:15 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_vars_atoi(t_vars *vars, char *argv[]);
static int	init_vars_sem(t_vars *vars);
//static int	philo_new(int i, t_vars *vars, void *(*routine)(void *));

int	init_vars(t_vars *vars, char *argv[])
{
	vars->stop = 0;
	if (init_vars_atoi(vars, argv))
		return (1);
	vars->philos = malloc(sizeof(pid_t) * vars->nb_philos);
	if (!vars->philos)
		return (1);
	if (init_vars_sem(vars))
		return (clean_vars(vars));
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

static int	init_vars_sem(t_vars *vars)
{
	// sem_close(vars->sem_stop);
	// sem_unlink(SEM_STOP);

	vars->sem_stop = sem_open(SEM_STOP, O_CREAT | O_EXCL, 0644, 1);
	// vars->sem_print = sem_open("sem_print", O_CREAT | O_EXCL, 1);
	// vars->sem_nb_philos_to_finish = sem_open("sem_nb_philos_to_finish",
	// 	O_CREAT | O_EXCL, vars->nb_philos_to_finish);
	
	perror(NULL);

	if (vars->sem_stop == SEM_FAILED)
		// || vars->sem_print == SEM_FAILED
		// || vars->sem_nb_philos_to_finish == SEM_FAILED
		// || sem_wait(vars->sem_stop))
		return (1);
	//printf("inf loop where?\n");
	return (0);
}

// static int	philo_new(int i, t_vars *vars, void *(*routine)(void *))
// {
// 	t_philo	*philo;
// 	int		index;

// 	(void)routine;

// 	philo = &vars->philos[i];
// 	philo->vars = vars;
// 	philo->i = i;
// 	index = -1;
// 	while (++index < 6)
// 		philo->color[index] = RED[index];
// 	philo->color[3] = '1' + (philo->i % 7);
// 	if (vars->argc == 6)
// 		philo->nb_times_to_eat = vars->nb_times_to_eat;
// 	// if (pthread_create(&philo->thread, NULL, routine, &vars->philos[i])
// 	// 	|| pthread_mutex_init(&philo->fork_left, NULL)
// 	// 	|| pthread_mutex_init(&philo->mutex_time_last_meal, NULL))
// 	// 	return (1);
// 	return (0);
// }

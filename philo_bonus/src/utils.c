/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:56:18 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/11 19:41:15 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philos_alive(t_vars *vars)
{
	int	result;

	result = 0;
	//pthread_mutex_lock(&vars->mutex_stop);
	if (!vars->stop)
		result = 1;
	//pthread_mutex_unlock(&vars->mutex_stop);
	return (result);
}

void	print_message(t_philo *philo, char *msg)
{
	struct timeval	time_difference;
	struct timeval	time_start;
	struct timeval	time;
	long int		miliseconds;
	int				miliseconds_decimal;

	//pthread_mutex_lock(&philo->vars->mutex_print);
	time_start = philo->vars->time_start;
	if (gettimeofday(&time, NULL))
		return ;
	set_time_difference(&time_difference, &time_start, &time);
	miliseconds = time_difference.tv_sec * 1000
		+ time_difference.tv_usec / 1000;
	miliseconds_decimal = (int)(time_difference.tv_usec % 1000);
	if (!all_philos_alive(philo->vars))
	{
		//pthread_mutex_unlock(&philo->vars->mutex_print);
		return ;
	}
	printf("%s[%5ld.%03d] %d %s\n", philo->color,
		miliseconds, miliseconds_decimal, philo->i + 1, msg);
	//pthread_mutex_unlock(&philo->vars->mutex_print);
}

void	set_time_difference(struct timeval *difference,
			struct timeval *start, struct timeval *end)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (start->tv_usec > end->tv_usec)
	{
		a = 1000000;
		b = 1;
	}
	difference->tv_usec = end->tv_usec + a - start->tv_usec;
	difference->tv_sec = end->tv_sec - b - start->tv_sec;
}

int	clean_vars(t_vars *vars)
{
	int	i;

	printf("inf loop where?1\n");
	sem_wait(vars->sem_stop);
	vars->stop = 1;
	sem_post(vars->sem_stop);
	i = -1;
	while (++i < vars->nb_philos) ;
		//pthread_join(vars->philos[i].thread, NULL);
	i = -1;
	while (++i < vars->nb_philos)
	{
		//pthread_mutex_destroy(&vars->philos[i].fork_left);
		//pthread_mutex_destroy(&vars->philos[i].mutex_time_last_meal);
	}
	free(vars->philos);

	printf("inf loop where?2\n");

	sem_close(vars->sem_stop);
	sem_unlink(SEM_STOP);
	// sem_unlink(vars->sem_print);
	// sem_unlink(vars->sem_nb_philos_to_finish);
	
	//pthread_mutex_destroy(&vars->mutex_stop);
	//pthread_mutex_destroy(&vars->mutex_nb_philos_to_finish);
	//pthread_mutex_destroy(&vars->mutex_print);
	return (1);
}

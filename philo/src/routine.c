/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:06:13 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/03 17:41:18 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo);
static void	wait_interval(struct timeval *time_start, suseconds_t interval);
//static void	wait_until(t_philo *philo, suseconds_t interval);
void	print_message(t_philo *philo, char *msg);

void	set_time_difference(struct timeval *difference, 
			struct timeval *start, struct timeval *end);

void	*routine(void *pnt)
{
	t_philo	*philo;

	philo = (t_philo *)pnt;
	if (all_philos_alive(philo->vars) && philo->i % 2)
	{
		// if (usleep(philo->vars->time_to_eat * 1000))
		// 	return (NULL);
		wait_interval(&philo->vars->time_start, philo->vars->time_to_eat * 1000);
		//philo->time_to_die -= philo->vars->time_to_eat;
	}
	while (all_philos_alive(philo->vars) && (1 || (vars->argc == 6 && philo->nb_times_to_eat)))//&& philo->time_to_die > 0)
	{
		if (philo->vars->nb_philos != 1 && eat(philo))//not sure if first part of statement necessary to circumvent the rand case with only 1 philo and 1 fork, may occure with multiple as well
			return (NULL);

		print_message(philo, "is sleeping");
		usleep(philo->vars->time_to_sleep * 1000);
		//philo->time_to_die -= philo->vars->time_to_sleep;

		print_message(philo, "is thinking");
					
		if (philo->vars->argc == 6 && !philo->nb_times_to_eat)
			return (NULL);
	}
	return (NULL);
}

static int	eat(t_philo *philo)
{
	int	i_philo_right;
	
	if (pthread_mutex_lock(&philo->fork_left))
		return (1);
	print_message(philo, "has taken a fork");
	i_philo_right = philo->i + 1;
	if (i_philo_right == philo->vars->nb_philos)
		i_philo_right = 0;
	if (pthread_mutex_lock(&philo->vars->philos[i_philo_right].fork_left))
		return (1);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");

	usleep(philo->vars->time_to_eat * 1000);//gotta cahnge to custom waiting function
	
	philo->nb_times_to_eat--;
	
	//philo->time_to_die = philo->vars->time_to_die;
	if (gettimeofday(&philo->time_last_meal, NULL))
		return (1);

	if (pthread_mutex_unlock(&philo->vars->philos[i_philo_right].fork_left))
		return (1);
	if (pthread_mutex_unlock(&philo->fork_left))
		return (1);
	return (0);
}

int	all_philos_alive(t_vars *vars)
{
	int	result;
	
	result = 1;
	if (pthread_mutex_lock(&vars->mutex))
		return (0);
	if (vars->dead == 1)
		result = 0;
	if (pthread_mutex_unlock(&vars->mutex))
		return (0);
	return (result);
}

static void wait_interval(struct timeval *time_start, suseconds_t interval)
//static void	wait_until(t_philo *philo, suseconds_t interval)
{
	struct timeval	time;
	//struct timeval	*time_start;

	//time_start = &philo->vars->time_start;
	if (gettimeofday(&time, NULL))
		return ;
	while (((time.tv_sec - time_start->tv_sec) * 1000000 
			+ time.tv_usec - time_start->tv_usec) < interval)
	{
		usleep(100);
		if (gettimeofday(&time, NULL))
			return ;
	}
}

void	print_message(t_philo *philo, char *msg)
{
	struct timeval	time_difference;
	struct timeval	time_start;
	struct timeval	time;
	char			color[6];
	int				i;
	
	i = -1;
	while (++i < 6)
		color[i] = RED[i];
	color[3] = '1' + (philo->i % 7); 
	time_start = philo->vars->time_start;
	if (gettimeofday(&time, NULL))
		return ;
	set_time_difference(&time_difference, &time_start, &time);
	printf("%s[%5ld.%03d] %d %s\n",
		color, time_difference.tv_sec * 1000 + time_difference.tv_usec / 1000,
			(int)(time_difference.tv_usec % 1000), philo->i + 1, msg);
			//undo the int cast for mac
}

void	set_time_difference(struct timeval *difference, 
			struct timeval *start, struct timeval *end)
{
	int	a;
	int	b;
	
	a = 0;
	b = 0;
	if (end->tv_usec - start->tv_usec < 0)
	{
		a = 1000000;
		b = 1;
	}
	difference->tv_usec = end->tv_usec + a - start->tv_usec;
	difference->tv_sec = end->tv_sec - b - start->tv_sec;
}

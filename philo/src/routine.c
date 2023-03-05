/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:06:13 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/05 16:00:11 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo);
static void	wait_interval(struct timeval *time_start, suseconds_t interval);
//static void	wait_until(t_philo *philo, suseconds_t interval);
void	print_message(t_philo *philo, char *msg);

void	set_time_difference(struct timeval *difference, 
			struct timeval *start, struct timeval *end);

void	update_time_last_meal(t_philo *philo, struct timeval *time, int miliseconds);

void	*routine(void *pnt)
{
	t_philo	*philo;

	philo = (t_philo *)pnt;
	//printf("am i here 1 %d\n", philo->i);
	if (all_philos_alive(philo->vars) && philo->i % 2)
	{
		// if (usleep(philo->vars->time_to_eat * 1000))
		// 	return (NULL);
		wait_interval(&philo->vars->time_start, philo->vars->time_to_eat * 1000);
		//philo->time_to_die -= philo->vars->time_to_eat;
	}
	//printf("am i here 2 %d\n", philo->i);
	while (all_philos_alive(philo->vars))//&& philo->time_to_die > 0)
	{
		if (eat(philo))//not sure if first part of statement necessary to circumvent the rand case with only 1 philo and 1 fork, may occure with multiple as well
			break ;
	
		if (philo->vars->argc == 6 && !philo->nb_times_to_eat)
		{
			
			//philo->vars->nb_philos_to_finish--;	
			//printf("%d in end if1\n", philo->i + 1);	
			if (pthread_mutex_lock(&philo->vars->mutex2))
				return (0);
			//printf("%d in end if2\n", philo->i + 1);
			philo->vars->nb_philos_to_finish--;	
			if (pthread_mutex_unlock(&philo->vars->mutex2))
				return (0);	
			
			break ;
		}	
		
		if (!all_philos_alive(philo->vars))
			break;
		print_message(philo, "is sleeping");
		wait_interval(&philo->time_last_meal, (philo->vars->time_to_eat + philo->vars->time_to_sleep) * 1000);
		
		if (!all_philos_alive(philo->vars))
			break;
			
		print_message(philo, "is thinking");

		// if (philo->vars->argc == 6 && !philo->nb_times_to_eat)
		// {
			
		// 	//philo->vars->nb_philos_to_finish--;	
		// 	//printf("%d in end if1\n", philo->i + 1);	
		// 	if (pthread_mutex_lock(&philo->vars->mutex2))
		// 		return (0);
		// 	//printf("%d in end if2\n", philo->i + 1);
		// 	philo->vars->nb_philos_to_finish--;	
		// 	if (pthread_mutex_unlock(&philo->vars->mutex2))
		// 		return (0);	
			
		// 	break ;
		// }	
	}
	//printf("%d end\n", philo->i + 1);
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
	
	if (i_philo_right == philo->i || !all_philos_alive(philo->vars))//not sure if this hardcode is necessary
		return (1);	
	
	if (pthread_mutex_lock(&philo->vars->philos[i_philo_right].fork_left))
		return (1);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");


	//update_time_last_meal(philo, &philo->time_last_meal, philo->vars->time_to_eat + philo->vars->time_to_sleep);
	if (gettimeofday(&philo->time_last_meal, NULL))
		return (1);
		
	philo->nb_times_to_eat--;

	wait_interval(&philo->time_last_meal, philo->vars->time_to_eat * 1000);

	if (pthread_mutex_unlock(&philo->vars->philos[i_philo_right].fork_left))
		return (1);
	if (pthread_mutex_unlock(&philo->fork_left))
		return (1);
	return (0);
}

void	update_time_last_meal(t_philo *philo, struct timeval *time, int miliseconds)
{
	pthread_mutex_lock(&philo->lock_time);
	time->tv_usec += miliseconds * 1000;
	time->tv_sec += miliseconds / 1000;
	if (time->tv_usec > 1000000)
	{
		time->tv_usec -= 1000000;
		time->tv_sec += 1;
	}
	pthread_mutex_unlock(&philo->lock_time);
}

int	all_philos_alive(t_vars *vars)
{
	int	result;
	
	result = 0;
	if (pthread_mutex_lock(&vars->mutex))
	 	return (0);
	if (!vars->stop)
		result = 1;;
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
		usleep(1);
		if (gettimeofday(&time, NULL))
			return ;
	}
}

void	print_message(t_philo *philo, char *msg)
{
	struct timeval	time_difference;
	struct timeval	time_start;
	struct timeval	time;
	// char			color[6];
	// int				i;
	
	if (pthread_mutex_lock(&philo->vars->mutex_print))
		return ;
	
	// i = -1;
	// while (++i < 6)
	// 	color[i] = RED[i];
	// color[3] = '1' + (philo->i % 7); 
	time_start = philo->vars->time_start;
	if (gettimeofday(&time, NULL))
		return ;
	
	
	set_time_difference(&time_difference, &time_start, &time);

	if (!all_philos_alive(philo->vars))
	{
		pthread_mutex_unlock(&philo->vars->mutex_print);
		return ;
	}
	
	printf("%s[%5ld.%03d] %d %s\n",
		philo->color, time_difference.tv_sec * 1000 + time_difference.tv_usec / 1000,
			(int)(time_difference.tv_usec % 1000), philo->i + 1, msg);

	if (pthread_mutex_unlock(&philo->vars->mutex_print))
		return ;
}

void	set_time_difference(struct timeval *difference, 
			struct timeval *start, struct timeval *end)
{
	int	a;
	int	b;
	
	//printf("inside set time diff\n");
	a = 0;
	b = 0;
	if (start->tv_usec > end->tv_usec)
	{
		a = 1000000;
		b = 1;
	}
	difference->tv_usec = end->tv_usec + a - start->tv_usec;
	difference->tv_sec = end->tv_sec - b - start->tv_sec;
	//printf("finished time diff\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:43:30 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/04 13:10:43 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NUMBER_OF_PHILOSOPHERS 		1
# define TIME_TO_DIE 					2
# define TIME_TO_EAT 					3
# define TIME_TO_SLEEP 					4
# define NB_TIMES_EACH_PHILO_MUST_EAT	5

# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE		"\x1B[37m"
# define RESET		"\x1B[0m"

# define constchar image[]

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_vars
{	
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;

	int				argc;
	t_philo			*philos;

	int				nb_finished_philos;
	pthread_mutex_t	mutex;

	struct timeval	time_start;
}					t_vars;

typedef struct s_philo
{
	t_vars			*vars;
	
	int				i;
	//int				time_to_die;
	int				nb_times_to_eat;
	pthread_t		thread;
	pthread_mutex_t	fork_left;

	struct timeval	time_last_meal;
}					t_philo;

int		ft_atoi(const char *nptr);
void	*routine(void *vars);
int		init_vars(t_vars *vars, char *argv[]);
int		philo_new(int i, t_vars *vars, void *(*routine)(void *));
int		philo_free_all(t_vars *vars);

int		all_philos_alive(t_vars *vars);
void	set_time_difference(struct timeval *difference, 
			struct timeval *start, struct timeval *end);
void	print_message(t_philo *philo, char *msg);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:43:30 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/02/28 14:43:09 by kkaczoro         ###   ########.fr       */
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

# define BUFFER_SIZE 200

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_vars
{
	int				dead;

	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;

	pthread_t		buffer_philo[BUFFER_SIZE];
	pthread_mutex_t	buffer_fork[BUFFER_SIZE];
}					t_vars;

int		ft_atoi(const char *nptr);
void	*routine(void *vars);
int		init_vars(t_vars *vars, int argc, char *argv[]);
void	clean_vars(t_vars *vars);


#endif
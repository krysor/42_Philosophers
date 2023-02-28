/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:43:30 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/02/28 12:15:04 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NUMBER_OF_PHILOSOPHERS 					1
# define TIME_TO_DIE 								2
# define TIME_TO_EAT 								3
# define TIME_TO_SLEEP 								4
# define NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT 	5

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
	pthread_t	buffer[BUFFER_SIZE];
	int			nb_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_times_must_eat;
}					t_vars;

int		ft_atoi(const char *nptr);
void	init_vars(t_vars *vars, int argc, char *argv[]);
void	clean_vars(t_vars *vars);
void	*routine(void *vars);

#endif
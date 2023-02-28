/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:03:36 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/02/28 14:25:17 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_vars(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->nb_philos)
	{
		pthread_join(vars->buffer_philo[i], NULL);
		pthread_mutex_destroy(&vars->buffer_fork[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:36:08 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/02/18 17:42:53 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_return_min_one(t_vars *vars)
{
	return (-1);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	
	if (argc != 5 && argc != 6)
		return (1);

	//printf("%sargv[%d]: %d\n", RED, 1, ft_atoi(argv[1]));

	if (!pthread_create(vars->buffer[0], NULL, ft_return_min_one, &vars))
		printf("pthread_create failed\n");	


	return (0);
}

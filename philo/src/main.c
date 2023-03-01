/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:36:08 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/01 12:04:58 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	//printf("%sargv[%d]: %d\n", RED, 1, ft_atoi(argv[1]));
	if (argc != 5 && argc != 6)
		return (1);
	if (init_vars(&vars, argc, argv))
		return (2);
	philo_free_all(vars.philos);
	//system("leaks philo");
	return (0);
}
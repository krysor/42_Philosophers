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

void	*ft_return_min_one(void *vars)
{
	(void)vars;
	usleep(2000000);
	printf("thread executed\n");
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	
	if (argc != 5 && argc != 6)
		return (1);

	//printf("%sargv[%d]: %d\n", RED, 1, ft_atoi(argv[1]));
	(void)argv;
	
	//vars.buffer[0] = malloc(sizeof(pthread_t));

	if (!pthread_create(&vars.buffer[0], NULL, &ft_return_min_one, &vars))
		printf("pthread_create succeded\n");
	else
		printf("pthread_create failed\n");

	//usleep(3000000);

	return (0);
}

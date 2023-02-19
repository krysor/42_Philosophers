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

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (1);
		
	int	i = 1;
	printf("%sargv[%d]: %d\n", RED, i, ft_atoi(argv[i]));
	i++;
	printf("%sargv[%d]: %d\n", GREEN, i, ft_atoi(argv[i]));
	i++;
	printf("%sargv[%d]: %d\n", YELLOW, i, ft_atoi(argv[i]));
	i++;
	printf("%sargv[%d]: %d\n", BLUE, i, ft_atoi(argv[i]));
	i++;
	printf("%sargv[%d]: %d\n", MAGENTA, i, ft_atoi(argv[i]));

	return (0);
}
#include "philo.h"

int	all_philos_alive(t_vars *vars)
{
	int	result;
	
	result = 0;
	if (pthread_mutex_lock(&vars->mutex_stop))
	 	return (0);
	if (!vars->stop)
		result = 1;;
	if (pthread_mutex_unlock(&vars->mutex_stop))
	 	return (0);
	return (result);
}

int	clean_all(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->nb_philos)
		pthread_join(vars->philos[i].thread, NULL);
	i = -1;
	while (++i < vars->nb_philos)
	{
		pthread_mutex_destroy(&vars->philos[i].fork_left);
		pthread_mutex_destroy(&vars->philos[i].mutex_time_last_meal);
	}
	free(vars->philos);
	pthread_mutex_destroy(&vars->mutex_stop);
	pthread_mutex_destroy(&vars->mutex_nb_philos_to_finish);
	pthread_mutex_destroy(&vars->mutex_print);
	return (1);
}
#include "philo_one.h"

int		fill_general_info(t_info *info, int argc, char **argv)
{
	info->philos_number = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		info->meals_to_eat = ft_atoi(argv[5]);
		if (info->meals_to_eat < 0)
			return (INVALID_ARGUMENTS);
	}
	else
		info->meals_to_eat = -1;
	if (info->philos_number < 2 || info->time_to_die <= 0 ||
		info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (INVALID_ARGUMENTS);
	return (0);
}

void	add_philos(t_info *info)
{
	int i;

	i = 0;
	while (i < info->philos_number)
	{
		info->philo[i].name = i + 1;
		info->philo[i].finished_meals = 0;
		info->philo[i].left_index = i;
		info->philo[i].right_index = (i + 1) % info->philos_number;
		info->philo[i].general_info = info;
		pthread_mutex_init(&(info->philo[i].dead), NULL);
		pthread_mutex_init(&(info->philo[i].permission), NULL);
		pthread_mutex_lock(&(info->philo[i].permission));
		pthread_mutex_init(&(info->philo[i].resume), NULL);
		pthread_mutex_lock(&(info->philo[i].resume));
		i++;
	}
}

int		init_mutexes(t_info *info)
{
	int i;

	i = 0;
	while (i < info->philos_number)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL) != 0)
			return (MUTEX_ERROR);
		i++;
	}
	if (pthread_mutex_init(&(info->output), NULL) != 0)
		return (MUTEX_ERROR);
	if (pthread_mutex_init(&(info->main_exit), NULL) != 0)
		return (MUTEX_ERROR);
	pthread_mutex_lock(&(info->main_exit));
	return (0);
}

int		fill_info(t_info *info, int argc, char **argv)
{
	if (fill_general_info(info, argc, argv) != 0)
		return (INVALID_ARGUMENTS);
	if (!(info->philo = (t_philo*)malloc(sizeof(t_philo) *
									info->philos_number)))
		return (MALLOC_ERROR);
	add_philos(info);
	if (!(info->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) *
													info->philos_number)))
		return (MALLOC_ERROR);
	if (init_mutexes(info) != 0)
		return (MUTEX_ERROR);
	return (0);
}

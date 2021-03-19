#include "philo_one.h"

void	free_info(t_info *info)
{
	int i;

	if (info->philo != NULL)
		free(info->philo);
	if (info->forks != NULL)
	{
		i = 0;
		while (i < info->philos_number)
		{
			pthread_mutex_destroy(&(info->forks[i]));
			i++;
		}
		free(info->forks);
	}
	pthread_mutex_destroy(&(info->output));
}

int		ft_error(char *error, t_info *info, int error_code)
{
	ft_putstr(error);
	if (error_code == INVALID_ARGUMENTS)
		ft_putstr("invalid arguments\n");
	else if (error_code == MALLOC_ERROR)
		ft_putstr("malloc error");
	else if (error_code == MUTEX_ERROR)
		ft_putstr("mutex error");
	else if (error_code == THREAD_ERROR)
		ft_putstr("thread error");
	free_info(info);
	return (-1);
}

int		main(int argc, char **argv)
{
	t_info	info;
	int		ret_value;

	info.philo = NULL;
	info.forks = NULL;
	if (argc < 5 || argc > 6)
	{
		ft_putstr("wrong number of arguments\n");
		return (0);
	}
	ret_value = fill_info(&info, argc, argv);
	if (ret_value != 0)
		return (ft_error("Error: ", &info, ret_value));
	ret_value = create_threads(&info);
	if (ret_value != 0)
		return (ft_error("Error: ", &info, ret_value));
	pthread_mutex_lock(&(info.main_exit));
	free_info(&info);
	return (0);
}

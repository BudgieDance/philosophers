#include "philo_three.h"

void	free_info(t_info *info)
{
	int i;

	sem_unlink(FORK_SEM);
	sem_unlink(MAIN_SEM);
	sem_unlink(OUTPUT_SEM);
	sem_unlink(HUNGRY_PHILOS);
	sem_unlink(EAT_PERM);
	i = 0;
	if (info->philo != NULL)
	{
		while (i < info->philos_number)
		{
			kill(info->philo[i].pid, SIGKILL);
			i++;
		}
		free(info->philo);
	}
}

int		ft_error(char *error, t_info *info, int error_code)
{
	ft_putstr(error);
	if (error_code == INVALID_ARGUMENTS)
		ft_putstr("invalid arguments\n");
	else if (error_code == MALLOC_ERROR)
		ft_putstr("malloc error");
	else if (error_code == SEM_ERROR)
		ft_putstr("semaphor error");
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
	sem_unlink(FORK_SEM);
	sem_unlink(MAIN_SEM);
	sem_unlink(OUTPUT_SEM);
	sem_unlink(HUNGRY_PHILOS);
	sem_unlink(EAT_PERM);
	if (argc < 5 || argc > 6)
	{
		ft_putstr("wrong number of arguments\n");
		return (0);
	}
	ret_value = fill_info(&info, argc, argv);
	if (ret_value != 0)
		return (ft_error("Error: ", &info, ret_value));
	ret_value = create_procs_and_threads(&info);
	if (ret_value != 0)
		return (ft_error("Error: ", &info, ret_value));
	sem_wait(info.main_sem);
	free_info(&info);
	return (0);
}

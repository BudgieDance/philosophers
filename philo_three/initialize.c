#include "philo_three.h"

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
		info->count_meals = 1;
	}
	else
	{
		info->meals_to_eat = -1;
		info->count_meals = 0;
	}
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
		info->philo[i].general_info = info;
		info->philo[i].dead = sem_open("dead", O_CREAT, 0644, 1);
		sem_unlink("dead");
		i++;
	}
}

int		open_semaphores(t_info *info)
{
	info->main_sem = sem_open(MAIN_SEM, O_CREAT, 0644, 0);
	if (info->main_sem == SEM_FAILED)
		return (SEM_ERROR);
	info->fork_sem = sem_open(FORK_SEM, O_CREAT, 0644, info->philos_number);
	if (info->fork_sem == SEM_FAILED)
		return (SEM_ERROR);
	info->output_sem = sem_open(OUTPUT_SEM, O_CREAT, 0644, 1);
	if (info->output_sem == SEM_FAILED)
		return (SEM_ERROR);
	info->hungry_philos = sem_open(HUNGRY_PHILOS, O_CREAT, 0644, 0);
	if (info->hungry_philos == SEM_FAILED)
		return (SEM_ERROR);
	info->eat_permission = sem_open(EAT_PERM, O_CREAT, 0644,
									(info->philos_number / 2));
	if (info->eat_permission == SEM_FAILED)
		return (SEM_ERROR);
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
	if (open_semaphores(info) != 0)
		return (SEM_ERROR);
	return (0);
}

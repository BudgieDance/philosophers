#include "philo_one.h"

void	*all_philos_finished(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info*)arg;
	i = 0;
	while (i < info->philos_number)
	{
		if (info->philo[i].finished_meals >= info->meals_to_eat)
			i++;
		else
			i = 0;
		usleep(3000);
	}
	pthread_mutex_lock(&(info->output));
	printf("All philosophers ate at least %d times\n", info->meals_to_eat);
	pthread_mutex_unlock(&(info->main_exit));
	return (NULL);
}

void	*monitor_health(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->dead));
		philo->death_time = get_time();
		if (philo->death_time > philo->next_death_time)
		{
			pthread_mutex_lock(&(philo->general_info->output));
			philo->death_time = philo->death_time -
					philo->general_info->start_time;
			printf("%ld %d is dead\n", philo->death_time, philo->name);
			pthread_mutex_unlock(&(philo->general_info->main_exit));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->dead));
		usleep(3000);
	}
	return (NULL);
}

void	*philo_main(void *arg)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo*)arg;
	philo->next_death_time = get_time() + philo->general_info->time_to_die;
	if (pthread_create(&thread, NULL, &monitor_health, philo) != 0)
		return (NULL);
	if (pthread_detach(thread) != 0)
		return (NULL);
	while (1)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		pthread_mutex_lock(&(philo->general_info->output));
		philo->action_time = get_time() - philo->general_info->start_time;
		print_output(philo, "is thinking");
		pthread_mutex_unlock(&(philo->general_info->output));
	}
	return (NULL);
}

void	*control_philos(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info*)arg;
	info->start_time = get_time();
	while (1)
	{
		i = 0;
		while (i < info->philos_number)
		{
			pthread_mutex_unlock(&(info->philo[i].permission));
			pthread_mutex_lock(&(info->philo[i].resume));
			i = i + 2;
		}
		i = 1;
		while (i < info->philos_number)
		{
			pthread_mutex_unlock(&(info->philo[i].permission));
			pthread_mutex_lock(&(info->philo[i].resume));
			i = i + 2;
		}
	}
	return (NULL);
}

int		create_philos_threads(t_info *info)
{
	int			i;
	pthread_t	thread;

	if (info->meals_to_eat != -1)
	{
		if (pthread_create(&thread, NULL, &all_philos_finished, info) != 0)
			return (THREAD_ERROR);
		if (pthread_detach(thread) != 0)
			return (THREAD_ERROR);
	}
	i = 0;
	while (i < info->philos_number)
	{
		if (pthread_create(&thread, NULL, &philo_main, &(info->philo[i])) != 0)
			return (THREAD_ERROR);
		if (pthread_detach(thread) != 0)
			return (THREAD_ERROR);
		i++;
	}
	pthread_create(&thread, NULL, &control_philos, info);
	pthread_detach(thread);
	return (0);
}

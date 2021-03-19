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
	}
	pthread_mutex_lock(&(info->output));
	ft_putstr("All philosophers ate at least ");
	ft_putnbr(info->meals_to_eat);
	ft_putstr(" times. Exit program\n");
	pthread_mutex_unlock(&(info->main_exit));
	return (NULL);
}

void	*monitor_health(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	while (1)
	{
		philo->death_time = get_time();
		if (philo->death_time > philo->next_death_time)
		{
			philo_status_print(philo, DEAD);
			pthread_mutex_unlock(&(philo->general_info->main_exit));
			return (NULL);
		}
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
		philo->action_time = get_time();
		philo_status_print(philo, THINKING);
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
	return (0);
}

int		create_threads(t_info *info)
{
	info->start_time = get_time();
	if (create_philos_threads(info) != 0)
		return (THREAD_ERROR);
	return (0);
}

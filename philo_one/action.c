#include "philo_one.h"

void	philo_take_forks(t_philo *philo)
{
	if (philo->name % 2 == 1)
	{
		pthread_mutex_lock(&(philo->general_info->forks[philo->left_index]));
		philo->action_time = get_time();
		philo_status_print(philo, TOOK_FORK);
		pthread_mutex_lock(&(philo->general_info->forks[philo->right_index]));
		philo->action_time = get_time();
		philo_status_print(philo, TOOK_FORK);
	}
	else
	{
		pthread_mutex_lock(&(philo->general_info->forks[philo->right_index]));
		philo->action_time = get_time();
		philo_status_print(philo, TOOK_FORK);
		pthread_mutex_lock(&(philo->general_info->forks[philo->left_index]));
		philo->action_time = get_time();
		philo_status_print(philo, TOOK_FORK);
	}
}

void	philo_eat(t_philo *philo)
{
	philo->next_death_time = get_time() + philo->general_info->time_to_die;
	philo->action_time = get_time();
	philo_status_print(philo, EATING);
	usleep(philo->general_info->time_to_eat * 1000);
	(philo->finished_meals)++;
	if (philo->name % 2 == 1)
	{
		pthread_mutex_unlock(&(philo->general_info->forks[philo->left_index]));
		pthread_mutex_unlock(&(philo->general_info->forks[philo->right_index]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->general_info->forks[philo->right_index]));
		pthread_mutex_unlock(&(philo->general_info->forks[philo->left_index]));
	}
}

void	philo_sleep(t_philo *philo)
{
	philo->action_time = get_time();
	philo_status_print(philo, SLEEPING);
	usleep(philo->general_info->time_to_sleep * 1000);
}

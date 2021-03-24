#include "philo_one.h"

void	print_output(t_philo *philo, char *output)
{
	printf("%ld %d %s\n", philo->action_time, philo->name, output);
}

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->permission));
	pthread_mutex_lock(&(philo->general_info->forks[philo->left_index]));
	pthread_mutex_lock(&(philo->general_info->output));
	philo->action_time = get_time() - philo->general_info->start_time;
	print_output(philo, "took a fork");
	pthread_mutex_unlock(&(philo->general_info->output));

	pthread_mutex_lock(&(philo->general_info->forks[philo->right_index]));
	pthread_mutex_lock(&(philo->general_info->output));
	philo->action_time = get_time() - philo->general_info->start_time;
	print_output(philo, "took a fork");
	pthread_mutex_unlock(&(philo->general_info->output));
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->dead));
	pthread_mutex_lock(&(philo->general_info->output));
	philo->next_death_time = get_time() + philo->general_info->time_to_die;
	philo->action_time = get_time() - philo->general_info->start_time;
	print_output(philo, "is eating");
	pthread_mutex_unlock(&(philo->resume));
	pthread_mutex_unlock(&(philo->general_info->output));
	pthread_mutex_unlock(&(philo->dead));
	usleep(philo->general_info->time_to_eat * 1000);
	(philo->finished_meals)++;
	pthread_mutex_unlock(&(philo->general_info->forks[philo->left_index]));
	pthread_mutex_unlock(&(philo->general_info->forks[philo->right_index]));
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->general_info->output));
	philo->action_time = get_time() - philo->general_info->start_time;
	print_output(philo, "is sleeping");
	pthread_mutex_unlock(&(philo->general_info->output));
	usleep(philo->general_info->time_to_sleep * 1000);
}

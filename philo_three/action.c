#include "philo_three.h"

void	print_output(t_philo *philo, char *output)
{
	printf("%ld %d %s\n", philo->action_time, philo->name, output);
}

void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->general_info->eat_permission);
	sem_wait(philo->general_info->fork_sem);
	sem_wait(philo->general_info->output_sem);
	philo->action_time = get_time() - philo->general_info->start_time;
	print_output(philo, "took a fork");
	sem_post(philo->general_info->output_sem);
	sem_wait(philo->general_info->fork_sem);
	sem_wait(philo->general_info->output_sem);
	philo->action_time = get_time() - philo->general_info->start_time;
	print_output(philo, "took a fork");
	sem_post(philo->general_info->output_sem);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->dead);
	sem_wait(philo->general_info->output_sem);
	philo->next_death_time = get_time() + philo->general_info->time_to_die;
	philo->action_time = get_time() - philo->general_info->start_time;
	print_output(philo, "is eating");
	sem_post(philo->general_info->output_sem);
	sem_post(philo->dead);
	usleep(philo->general_info->time_to_eat * 1000);
	if (philo->general_info->count_meals == 1)
	{
		(philo->finished_meals)++;
		if (philo->finished_meals == philo->general_info->meals_to_eat)
			sem_post(philo->general_info->hungry_philos);
	}
	sem_post(philo->general_info->fork_sem);
	sem_post(philo->general_info->fork_sem);
	sem_post(philo->general_info->eat_permission);
}

void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->general_info->output_sem);
	philo->action_time = get_time() - philo->general_info->start_time;
	print_output(philo, "is sleeping");
	sem_post(philo->general_info->output_sem);
	usleep(philo->general_info->time_to_sleep * 1000);
}

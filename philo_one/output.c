#include "philo_one.h"

void	print_timestamp(long int action, long int start)
{
	int time;

	time = (int)(action - start);
	ft_putnbr(time);
	ft_putchar(' ');
}

void	philo_status_print(t_philo *philo, int status)
{
	pthread_mutex_lock(&(philo->general_info->output));
	if (status == DEAD)
	{
		print_timestamp(philo->death_time, philo->general_info->start_time);
		ft_putnbr(philo->name);
		ft_putstr(" died\n");
		return ;
	}
	print_timestamp(philo->action_time, philo->general_info->start_time);
	ft_putnbr(philo->name);
	if (status == TOOK_FORK)
		ft_putstr(" has taken a fork\n");
	else if (status == EATING)
		ft_putstr(" is eating\n");
	else if (status == SLEEPING)
		ft_putstr(" is sleeping\n");
	else if (status == THINKING)
		ft_putstr(" is thinking\n");
	pthread_mutex_unlock(&(philo->general_info->output));
}

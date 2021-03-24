#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

struct s_info;
struct s_philo;
struct timeval timestamp;

typedef struct	s_philo
{
	int				name;
	int				left_index;
	int				right_index;
	int				finished_meals;
	int				state;
	long int		action_time;
	long int		death_time;
	long int		next_death_time;
	pthread_mutex_t	dead;
	pthread_mutex_t	permission;
	pthread_mutex_t resume;
	struct s_info	*general_info;
}				t_philo;

typedef struct	s_info
{
	int				philos_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	long int		start_time;
	pthread_mutex_t	main_exit;
	pthread_mutex_t	output;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}				t_info;

typedef enum	e_error
{
	INVALID_ARGUMENTS = 1,
	MALLOC_ERROR,
	MUTEX_ERROR,
	THREAD_ERROR
}				t_error;

/*
**UTILS
*/
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
void			ft_putstr(char *s);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strdup(const char *s);
void			ft_putnbr(int n);
void			ft_putchar(char c);
long int		get_time(void);

/*
**INITIALIZE
*/
int				fill_info(t_info *info, int argc, char **argv);
int				create_threads(t_info *info);

/*
**ACTION
*/
void			philo_take_forks(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);

/*
**OUTPUT
*/
void			print_output(t_philo *philo, char *output);
#endif

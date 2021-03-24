#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# define FORK_SEM "forks"
# define MAIN_SEM "main"
# define OUTPUT_SEM "output"
# define HUNGRY_PHILOS "hungry philos"
# define EAT_PERM "eat_permission"

struct s_info;
struct timeval timestamp;

typedef struct	s_philo
{
	int				name;
	int				finished_meals;
	pid_t			pid;
	long int		action_time;
	long int		death_time;
	long int		next_death_time;
	sem_t			*dead;
	struct s_info	*general_info;
}				t_philo;

typedef struct	s_info
{
	int				philos_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				count_meals;
	long int		start_time;
	sem_t			*eat_permission;
	sem_t			*fork_sem;
	sem_t			*output_sem;
	sem_t			*main_sem;
	sem_t			*hungry_philos;
	t_philo			*philo;
}				t_info;

typedef enum	e_error
{
	INVALID_ARGUMENTS = 1,
	MALLOC_ERROR,
	SEM_ERROR,
	THREAD_ERROR
}				t_error;

/*
**UTILS
*/
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *nptr);
void			ft_putstr(char *s);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strdup(const char *s);
long int		get_time(void);

/*
**INITIALIZE
*/
int				fill_info(t_info *info, int argc, char **argv);
int				create_procs_and_threads(t_info *info);

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

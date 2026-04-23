# ifndef HEADER_H
# define HEADER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "string.h"

#define	MAX_PHILO 200

#define EAT_STR "is eating"
#define SLEEP_STR "is sleeping"
#define THINK_STR "is thinking"
#define FORK_STR "has taken a fork"
#define DEATH_STR "is death"

#define CHECK_ERR(fn_call)\
do { \
  int err = (fn_call); \
  if (err != 0) \
      printf("[%d, %s] %s -> %s thread_id: %lu\n", __LINE__, __FILE_NAME__, #fn_call, strerror(err), (unsigned long)pthread_self());\
} while (0)

typedef enum e_state
{
	THINKING,
	SLEEPING,
	EATING
} t_state;

typedef struct s_philo t_philo;

typedef struct s_shared
{
	int		n_philo;
	int		must_eat;
	int		stop;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_think;
	long	time_to_sleep;
	long	start_time;
	pthread_mutex_t forks[MAX_PHILO];
	pthread_mutex_t stop_lock;
	pthread_mutex_t write_lock;
} t_shared;

typedef struct s_philo
{
	pthread_t	thread;
	t_shared	*shared;
	int			id;
	int			meal_eaten;
	int			dead;
	long		last_meal;
	t_state			state;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t dead_lock;
	pthread_mutex_t meal_eaten_lock;
	pthread_mutex_t last_meal_lock;
} t_philo;

///////////////////////// ACTIONS.C /////////////////////////
int	eating(struct s_philo *philo);
int	sleeping(struct s_philo *philo);
int	thinking(struct s_philo *philo);
int	print_action(struct s_philo *philo, char *action);

///////////////////////// UTILS.C /////////////////////////
long get_current_time(void);
int	ft_usleep(size_t milliseconds);
long	last_meal_elapsed_time(t_philo *philo);

///////////////////////// SHARED.C /////////////////////////
int	update_shared_value(pthread_mutex_t *mutex, int *shared_value);
int	read_shared_value(pthread_mutex_t *mutex, int *shared_value);
long	read_last_meal(t_philo *philo);
long	update_last_meal(t_philo *philo);

///////////////////////// ROUTINE.C /////////////////////////
void	*routine(void *arg);
void	*routine_monitor(void *arg);

///////////////////////// CLEAR.C /////////////////////////
int	clear_philo(t_philo *philo[]);

# endif

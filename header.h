# ifndef HEADER_H
# define HEADER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "string.h"


#define	NB_PHILO 4

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
	int		numbers_of_philo;
	int		nb_meal_to_eat;
	int		stop;
	size_t	time_to_eat;
	size_t	time_to_die;
	size_t	time_to_think;
	size_t	time_to_sleep;
	size_t	start_time;
	pthread_mutex_t *write_lock;
	pthread_mutex_t	*forks;
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
} t_philo;

typedef struct s_monitor
{
	pthread_t	thread;
	t_shared	*shared;
	t_philo		**philo;
} t_monitor;

///////////////////////// ACTIONS.C /////////////////////////
void	eating(struct s_philo *philo);
void	sleeping(struct s_philo *philo);
void	thinking(struct s_philo *philo);
void	print_action(struct s_philo *philo, char *action);

///////////////////////// UTILS.C /////////////////////////
long get_current_time(void);
int	ft_usleep(size_t milliseconds);

# endif

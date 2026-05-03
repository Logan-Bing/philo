#ifndef HEADER_H
#define HEADER_H

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
# include <sys/time.h>

// Les fourchettes sont au milieu de la table
// Lancer les process(philo)
// Pseudo code :
// sem_t waiter = n_philo - 1;
// wait(waiter)
// wait(forks)
// wait(forks)
// eating()
// post(forks)
// post(forks)
// post( waiter)

// Arreter les process(philos)
//

// SEMAPHORE
/////////// Global: Forks, waiters
////////// Local: meal_eaten, last_meal, dead

# define MAX_PHILO 200

# define EAT_STR "is eating"
# define SLEEP_STR "is sleeping"
# define THINK_STR "is thinking"
# define FORK_STR "has taken a fork"
# define DEATH_STR "died"

#define SEM_DEATH "/death"
#define SEM_FULL "/full"
#define SEM_END "/end"
#define SEM_LAST_MEAL "/last_meal"
#define SEM_MEAL_EATEN "/meal_eaten"
#define SEM_PRINT "/print"
#define SEM_WAITERS "/waiters"
#define SEM_FORKS "/forks"
#define SEM_START "/start"

# define INT_MIN -2147483648
# define INT_MAX 2147483647
# define ARG_ERROR "Invalid numbers of arguments\n"
# define INPUT_ERROR "Invalide value present\n"

typedef struct s_shared
{
	int				philo_pid[MAX_PHILO];
	int				n_philo;
	int				must_eat;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	sem_t			*dead;
	sem_t			*full;
	sem_t			*end;
	sem_t			*print;
	sem_t			*waiters;
	sem_t			*forks;
	sem_t			*start;
}					t_shared;

typedef struct s_philo
{
	int		id;
	int		meal_eaten;
	long	last_meal;
	sem_t	*full;
	sem_t	*sem_meal_eaten;
	sem_t	*sem_last_meal;
	t_shared *shared;
}	t_philo;

///////////////////////// PARSING.C /////////////////////////
int		is_valid_data(t_shared *shared, int argc, char **argv);
int	is_valid_n_of_args(int argc);

///////////////////////// CLEAR.C /////////////////////////
void	clear_sem(void);
int		kill_philos(t_shared *shared);

///////////////////////// UTILS.C /////////////////////////
long	get_current_time(void);
int		ft_usleep(size_t milliseconds);
long	ft_atol(const char *str);
void	ft_bzero(void *s, size_t n);

///////////////////////// ACTION.C /////////////////////////
int		print_action(struct s_philo *philo, char *action);
int		eating(struct s_philo *philo);
int		sleeping(struct s_philo *philo);
int		thinking(struct s_philo *philo);

///////////////////////// SHARED_ACCESS.C /////////////////////////
long	last_meal_elapsed_time(t_philo *philo);
int	update_last_meal(t_philo *philo);

///////////////////////// SHARED_HELPERS.C /////////////////////////
int is_sated(t_philo *philo);
int	is_full(t_philo *philo);

///////////////////////// INIT.C /////////////////////////
int	init_shared_sem(t_shared *shared);

///////////////////////// ROUTINE.C /////////////////////////
void	*routine_death(void *arg);
void	*routine_full(void *arg);
void *local_routine(void *arg);
#endif

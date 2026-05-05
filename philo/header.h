/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:00:53 by llugez            #+#    #+#             */
/*   Updated: 2026/05/05 09:38:19 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "string.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200

# define EAT_STR "is eating"
# define SLEEP_STR "is sleeping"
# define THINK_STR "is thinking"
# define FORK_STR "has taken a fork"
# define DEATH_STR "died"

# define INT_MIN -2147483648
# define INT_MAX 2147483647
# define ARG_ERROR "Invalid numbers of arguments\n"
# define INPUT_ERROR "Invalide value present\n"

typedef struct s_shared
{
	int				stop;
	int				must_eat;
	int				n_philo;
	int				ate_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	write_lock;
}					t_shared;

typedef struct s_philo
{
	pthread_t		thread;
	t_shared		*shared;
	int				id;
	int				finish_eat;
	int				meal_eaten;
	int				dead;
	long			last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_eaten_lock;
	pthread_mutex_t	last_meal_lock;
}					t_philo;

///////////////////////// ACTIONS.C /////////////////////////
int					eating(struct s_philo *philo);
int					sleeping(struct s_philo *philo);
int					thinking(struct s_philo *philo);
int					print_action(struct s_philo *philo, char *action);

///////////////////////// INIT.C /////////////////////////
t_philo				**init_philos(t_shared *shared);
int					init_shared_mutex(t_shared *shared);
int					init_philos_mutex(t_philo **philos);

///////////////////////// UTILS.C /////////////////////////
long				get_current_time(void);
int					ft_usleep(t_shared *shared, size_t milliseconds);
long				last_meal_elapsed_time(t_philo *philo);
long				ft_atol(const char *str);

///////////////////////// SHARED_HELPERS.C /////////////////////////
int					update_shared_value(pthread_mutex_t *mutex,
						int *shared_value);
int					read_shared_value(pthread_mutex_t *mutex,
						int *shared_value);
long				read_last_meal(t_philo *philo);
long				update_last_meal(t_philo *philo);

///////////////////////// SHARED_ACCESS.C /////////////////////////
int					is_dead(t_philo *philo);
int					all_ate(t_philo *philo, int philos_ate_count);
int					has_philo_finish_eaten(t_philo *philo);

///////////////////////// PARSING.C /////////////////////////
int					is_valid_data(t_shared *shared, int argc, char *argv[]);

///////////////////////// ROUTINE.C /////////////////////////
void				*routine(void *arg);
void				*routine_monitor(void *arg);
int					start_philos_routine(t_philo **philos);

///////////////////////// CLEAR.C /////////////////////////
void				clear_all(t_philo **philo);

#endif

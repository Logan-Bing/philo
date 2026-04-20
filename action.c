#include "header.h"

void	print_action(struct s_philo *philo, char *action)
{
	long	timestamp;

	CHECK_ERR(pthread_mutex_lock(philo->shared->write_lock));
	timestamp = get_current_time() - philo->shared->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, action);
	CHECK_ERR(pthread_mutex_unlock(philo->shared->write_lock));
}

void	taking_fork(struct s_philo *philo)
{
	print_action(philo, FORK_STR);
	CHECK_ERR(pthread_mutex_lock());
}

void	eating(struct s_philo *philo)
{
	print_action(philo, EAT_STR);
	ft_usleep(philo->shared->time_to_eat);
	philo->meal_eaten++;
}

void	sleeping(struct s_philo *philo)
{
	print_action(philo, SLEEP_STR);
	ft_usleep(philo->shared->time_to_sleep);
}

void	thinking(struct s_philo *philo)
{
	print_action(philo, THINK_STR);
}

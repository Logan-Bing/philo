#include "header.h"

int	print_action(struct s_philo *philo, char *action)
{
	long	timestamp;

	CHECK_ERR(pthread_mutex_lock(&philo->shared->write_lock));
	timestamp = get_current_time() - philo->shared->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, action);
	CHECK_ERR(pthread_mutex_unlock(&philo->shared->write_lock));
	return (1);
}

int	eating(struct s_philo *philo)
{
	t_shared *shared = philo->shared;
	if (read_shared_value(&shared->stop_lock, &shared->stop))
			return (0);
	print_action(philo, FORK_STR);
	CHECK_ERR(pthread_mutex_lock(philo->left_fork));
	print_action(philo, FORK_STR);
	CHECK_ERR(pthread_mutex_lock(philo->right_fork));
	print_action(philo, EAT_STR);
	update_last_meal(philo);
	ft_usleep(philo->shared->time_to_eat);
	update_shared_value(&philo->meal_eaten_lock, &philo->meal_eaten);
	CHECK_ERR(pthread_mutex_unlock(philo->left_fork));
	CHECK_ERR(pthread_mutex_unlock(philo->right_fork));
	return (1);
}

int	sleeping(struct s_philo *philo)
{
	t_shared *shared = philo->shared;

	if (read_shared_value(&shared->stop_lock, &shared->stop))
			return (0);
	print_action(philo, SLEEP_STR);
	ft_usleep(philo->shared->time_to_sleep);
	return (1);
}

int	thinking(struct s_philo *philo)
{
	t_shared *shared = philo->shared;

	if (read_shared_value(&shared->stop_lock, &shared->stop))
			return (0);
	print_action(philo, THINK_STR);
	return (1);
}

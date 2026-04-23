#include "header.h"

int	update_shared_value(pthread_mutex_t *mutex, int *shared_value)
{
	CHECK_ERR(pthread_mutex_lock(mutex));
	(*shared_value)++;
	CHECK_ERR(pthread_mutex_unlock(mutex));
	return (*shared_value);
}

int	read_shared_value(pthread_mutex_t *mutex, int *shared_value)
{
	int	value;

	CHECK_ERR(pthread_mutex_lock(mutex));
	value = *shared_value;
	CHECK_ERR(pthread_mutex_unlock(mutex));
	return (value);
}

long	update_last_meal(t_philo *philo)
{
	CHECK_ERR(pthread_mutex_lock(&philo->last_meal_lock));
	philo->last_meal = get_current_time() - philo->shared->start_time;
	CHECK_ERR(pthread_mutex_unlock(&philo->last_meal_lock));
	return (1);
}

long	read_last_meal(t_philo *philo)
{
	int	value;

	CHECK_ERR(pthread_mutex_lock(&philo->last_meal_lock));
	value = philo->last_meal;
	CHECK_ERR(pthread_mutex_unlock(&philo->last_meal_lock));
	return (value);
}

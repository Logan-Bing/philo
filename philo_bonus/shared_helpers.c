#include "bonus.h"

int is_sated(t_philo *philo)
{
	return (last_meal_elapsed_time(philo) <= philo->shared->time_to_die);
}

int	is_full(t_philo *philo)
{
	t_shared 	*shared;
	int	value;

	shared = philo->shared;
	if (shared->must_eat == -1)
		return (0);
	sem_wait(philo->sem_meal_eaten);
	value = philo->meal_eaten;
	sem_post(philo->sem_meal_eaten);
	return (value >= shared->must_eat);
}

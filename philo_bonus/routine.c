#include "bonus.h"

void	*routine_death(void *arg)
{
	t_shared 	*shared;
	int			i;

	i = 0;
	shared = (t_shared *)arg;
	sem_wait(shared->dead);
	kill_philos(shared);
	if (shared->must_eat != -1)
	{
		while (i < shared->n_philo)
		{
			sem_post(shared->full);
			i++;
		}
	}
	sem_post(shared->end);
	return (NULL);
}

void	*routine_full(void *arg)
{
	t_shared *shared;
	int			philo_full;

	shared = (t_shared *)arg;
	philo_full = 0;
	while (philo_full < shared->n_philo)
	{
		sem_wait(shared->full);
		philo_full++;
	}
	kill_philos(shared);
	sem_post(shared->dead);
	sem_post(shared->end);
	return (NULL);
}

void *local_routine(void *arg)
{
	t_philo *philo;
	t_shared *shared;
	int	is_already_full;

	philo = (t_philo *)arg;
	shared = philo->shared;
	is_already_full = 0;
	while (is_sated(philo))
	{
		if (is_full(philo) && !is_already_full)
		{
			sem_post(shared->full);
			is_already_full = 1;
		}
		usleep(100);
	}
	print_action(philo, DEATH_STR);
	sem_post(shared->dead);
	return (NULL);
}

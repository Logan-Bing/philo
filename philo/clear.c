#include "header.h"

static void	clear_philo(t_philo *philo[])
{
	int	i;
	int	n_philo;

	i = 0;
	n_philo = philo[i]->shared->n_philo;
	while (i < n_philo)
	{
		pthread_join(philo[i]->thread, NULL);
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_destroy(&philo[i]->dead_lock);
		pthread_mutex_destroy(&philo[i]->meal_eaten_lock);
		pthread_mutex_destroy(&philo[i]->last_meal_lock);
		free(philo[i]);
		i++;
	}
	free(philo);
}

static void	clear_shared(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philo)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&shared->stop_lock);
	pthread_mutex_destroy(&shared->write_lock);
}

void	clear_all(t_philo **philo)
{
	t_shared	*shared;

	shared = philo[0]->shared;
	clear_philo(philo);
	clear_shared(shared);
}

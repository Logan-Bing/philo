#include "header.h"

t_philo	**init_philos(t_shared *shared)
{
	t_philo 		**philo;

	philo = malloc(sizeof(t_philo *) * shared->n_philo);
	if (!philo)
		return (NULL);
	for (int i = 0; i < shared->n_philo; i++)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		philo[i]->shared = shared;
		philo[i]->finish_eat = 0;
		philo[i]->state = SLEEPING;
		philo[i]->dead = 0;
		philo[i]->id = i + 1;
		philo[i]->left_fork = &shared->forks[i];
		philo[i]->right_fork = &shared->forks[(i + 1) % shared->n_philo];
		if (shared->n_philo == 1)
			philo[i]->right_fork = NULL;
		pthread_mutex_init(&philo[i]->dead_lock, &attr);
		pthread_mutex_init(&philo[i]->meal_eaten_lock, &attr);
		pthread_mutex_init(&philo[i]->last_meal_lock, &attr);
	}
	return (philo);
}

int	init_shared_mutex(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philo)
	{
		pthread_mutex_init(&shared->forks[i], &attr);
		i++;
	}
	pthread_mutex_init(&shared->stop_lock, &attr);
	pthread_mutex_init(&shared->write_lock, &attr);
	return (1);
}


#include "header.h"

int	start_philos_routine(t_philo **philos)
{
	int	i;
	t_shared *shared;

	i = 0;
	shared = philos[i]->shared;
	shared->start_time = get_current_time();
	while (i < shared->n_philo)
	{
		if (pthread_create(&philos[i]->thread, NULL, routine, philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

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
		philo[i]->last_meal = 0;
		philo[i]->meal_eaten = 0;
		philo[i]->finish_eat = 0;
		philo[i]->dead = 0;
		philo[i]->id = i + 1;
		philo[i]->left_fork = &shared->forks[i];
		philo[i]->right_fork = &shared->forks[(i + 1) % shared->n_philo];
		if (shared->n_philo == 1)
			philo[i]->right_fork = NULL;
		pthread_mutex_init(&philo[i]->dead_lock, NULL);
		pthread_mutex_init(&philo[i]->meal_eaten_lock, NULL);
		pthread_mutex_init(&philo[i]->last_meal_lock, NULL);
	}
	return (philo);
}

int	init_shared_mutex(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philo)
	{
		pthread_mutex_init(&shared->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&shared->stop_lock, NULL);
	pthread_mutex_init(&shared->write_lock, NULL);
	return (1);
}


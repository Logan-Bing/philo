#include "header.h"

pthread_mutexattr_t attr;

t_philo	**init_philos(t_shared *shared)
{
	t_philo 		**philo;

	for (int i = 0; i < shared->n_philo; i++)
		pthread_mutex_init(&shared->forks[i], &attr);
	philo = malloc(sizeof(t_philo *) * shared->n_philo);
	if (!philo)
		return (NULL);
	for (int i = 0; i < shared->n_philo; i++)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		philo[i]->shared = shared;
		philo[i]->state = SLEEPING;
		philo[i]->dead = 0;
		philo[i]->id = i + 1;
		philo[i]->left_fork = &shared->forks[i];
		philo[i]->right_fork = &shared->forks[(i + 1) % shared->n_philo];
		pthread_mutex_init(&philo[i]->dead_lock, &attr);
		pthread_mutex_init(&philo[i]->meal_eaten_lock, &attr);
		pthread_mutex_init(&philo[i]->last_meal_lock, &attr);
	}
	return (philo);
}

int main(int argc, char *argv[])
{
	//////////////// DEV ////////////////////////////////////
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	//////////////// DEV ////////////////////////////////////
	

	// t_shared shared = {
	// 	.stop = 0,
	// 	.n_philo = NB_PHILO, 
	// 	.time_to_die = 810,
	// 	.time_to_eat = 440,
	// 	.time_to_sleep = 200,
	// 	.must_eat = 100,
	// 	.time_to_think = 0,
	// };
	//
	// pthread_mutex_init(&shared.stop_lock, &attr);
	// pthread_mutex_init(&shared.write_lock, &attr);
	//
	//
	// // Trouver une solution pour les faire commencer en meme temps
	// shared.start_time = get_current_time();
	// for (int i = 0; i < NB_PHILO; i++)
	// {
	// 	pthread_create(&philo[i]->thread, NULL, routine, philo[i]);
	// }
	//
	// pthread_create(&monitor, NULL, routine_monitor, philo);
	// pthread_join(monitor, NULL);
	//
	// clear_philo(philo);
}

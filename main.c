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

int main(int argc, char *argv[])
{
	//////////////// DEV ////////////////////////////////////
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	//////////////// DEV ////////////////////////////////////
	t_shared	shared;
	t_philo		**philos;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
	{
		write(2, ARG_ERROR, 29);
		return (1);
	}
	shared = (t_shared){
		.stop = 0,
		.n_philo = ft_atol(argv[1]),
		.time_to_die = ft_atol(argv[2]),
		.time_to_eat = ft_atol(argv[3]),
		.time_to_sleep = ft_atol(argv[4]),
		.must_eat = -1
	};
	if (!is_valid_data(&shared, argc, argv))
		return (1);
	init_shared_mutex(&shared);
	philos = init_philos(&shared);
	if (!start_philos_routine(philos))
	{
		write(2, THREAD_ERROR, 20);
		return (1);
	}
	pthread_create(&monitor, NULL, routine_monitor, philos);
	pthread_join(monitor, NULL);
	clear_philo(philos);
}

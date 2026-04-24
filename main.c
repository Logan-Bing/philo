#include "header.h"

static int	is_valid_n_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(2, ARG_ERROR, 29);
		return (0);
	}
	return (1);
}

int main(int argc, char *argv[])
{
	t_shared	shared;
	t_philo		**philos;
	pthread_t	monitor;

	if (!is_valid_n_of_args(argc))
		return (1);
	shared = (t_shared){
		.stop = 0,
		.n_philo = ft_atol(argv[1]),
		.time_to_die = ft_atol(argv[2]),
		.time_to_eat = ft_atol(argv[3]),
		.time_to_sleep = ft_atol(argv[4]),
		.philos_ate_count = 0,
		.must_eat = -1
	};
	if (!is_valid_data(&shared, argc, argv))
		return (1);
	init_shared_mutex(&shared);
	philos = init_philos(&shared);
	start_philos_routine(philos);
	pthread_create(&monitor, NULL, routine_monitor, philos);
	pthread_join(monitor, NULL);
	clear_all(philos);
}

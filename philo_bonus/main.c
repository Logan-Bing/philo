#include "bonus.h"

void	philo_main(t_shared *shared)
{
	int pid;
	pthread_t thread;
	t_philo philo;

	shared->start_time = get_current_time();
	for (int i = 0; i < shared->n_philo; i++)
	{
		pid = fork();
		if (pid == 0)
		{

			philo = (t_philo){
				.id = i + 1, 
				.shared = shared,
				.last_meal = 0,
				.meal_eaten = 0,
			};
			sem_wait(shared->start);
			pthread_create(&thread, NULL, local_routine, &philo);
			pthread_detach(thread);
			while (eating(&philo) && sleeping(&philo) && thinking(&philo));
		}
		shared->philo_pid[i] = pid;
	}
}

void	wait_for_philo(t_shared *shared)
{
	int i;

	i = 0;
	while (i < shared->n_philo)
	{
		sem_post(shared->start);
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_shared	shared;
	pthread_t	thread_death;
	pthread_t	thread_full;

	thread_full = NULL;
	clear_sem();
	if (!is_valid_n_of_args(argc))
		return (1);
	shared = (t_shared){.n_philo = ft_atol(argv[1]),
		.time_to_die = ft_atol(argv[2]), .time_to_eat = ft_atol(argv[3]),
		.time_to_sleep = ft_atol(argv[4]), .must_eat = -1};
	if (!is_valid_data(&shared, argc, argv))
		return (1);
	ft_bzero(shared.philo_pid, sizeof(int) * 200);
	init_shared_sem(&shared);
	philo_main(&shared);
	wait_for_philo(&shared);
	pthread_create(&thread_death, NULL, routine_death, &shared);
	pthread_detach(thread_full);
	if (shared.must_eat != -1)
	{
		pthread_create(&thread_full, NULL, routine_full, &shared);
		pthread_detach(thread_death);
	}
	sem_wait(shared.end);
	clear_sem();
	return (0);
}

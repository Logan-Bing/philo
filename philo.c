#include "header.h"

pthread_mutexattr_t attr;

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		ft_usleep(philo->shared->time_to_eat);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return NULL;
}

int main()
{
	pthread_mutex_t write_lock;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

	pthread_mutex_t forks[NB_PHILO];

	for (int i = 0; i < NB_PHILO; i++)
	{
		pthread_mutex_init(&forks[i], &attr);
	}

	pthread_mutex_init(&write_lock, &attr);
	t_shared shared = {
		.numbers_of_philo = NB_PHILO, 
		.time_to_die = 800,
		.time_to_eat = 200,
		.time_to_sleep = 200,
		.time_to_think = 10,
		.write_lock = &write_lock,
		.forks = forks
	};

	t_philo *philo[NB_PHILO];

	for (int i = 0; i < NB_PHILO; i++)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (1);
		philo[i]->shared = &shared;
		philo[i]->state = SLEEPING;
		philo[i]->id = i + 1;
		philo[i]->left_fork = &forks[i];
		philo[i]->right_fork = &forks[(i + 1) % NB_PHILO];
	}

	for (int i = 0; i < NB_PHILO; i++)
	{
		shared.start_time = get_current_time();
		pthread_create(&philo[i]->thread, NULL, routine, philo[i]);
	}

	for (int i = 0; i < NB_PHILO; i++)
	{
		pthread_join(philo[i]->thread, NULL);
	}
}

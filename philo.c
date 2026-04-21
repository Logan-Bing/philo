#include "header.h"

pthread_mutexattr_t attr;

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		ft_usleep(philo->shared->time_to_eat);
	while (1)
	{
		if (philo->shared->stop)
			return (NULL);
		eating(philo);
		if (philo->shared->stop)
			return (NULL);
		sleeping(philo);
		if (philo->shared->stop)
			return (NULL);
		thinking(philo);
		philo->dead = 1;
	}
	return NULL;
}

int	clear_philo(t_philo *philo[])
{
	int	i;

	i = 0;
	while (i < NB_PHILO)
	{
		if (pthread_join(philo[i]->thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	*routine_monitor(void *arg)
{
	t_monitor 	*monitor = (t_monitor *)arg;
	t_philo		**philo = monitor->philo;
	t_shared	*shared = monitor->shared;
	int i;
	while (1)
	{
		i = 0;
		while (i < NB_PHILO)
		{
			if (philo[i]->dead == 1)
			{
				monitor->shared->stop = 1;
				print_action(philo[i], DEATH_STR);
				break;
			}
			i++;
		}
		if (shared->stop)
			break;
		ft_usleep(100);
	}
	return (NULL);
}

int main()
{
	pthread_mutex_t write_lock;
	pthread_mutex_t forks[NB_PHILO];
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

	for (int i = 0; i < NB_PHILO; i++)
		pthread_mutex_init(&forks[i], &attr);

	pthread_mutex_init(&write_lock, &attr);
	t_shared shared = {
		.stop = 0,
		.numbers_of_philo = NB_PHILO, 
		.time_to_die = 800,
		.time_to_eat = 2000,
		.time_to_sleep = 2000,
		.nb_meal_to_eat = 0,
		.time_to_think = 0,
		.write_lock = &write_lock,
		.forks = forks
	};

	t_philo *philo[NB_PHILO];
	t_monitor	monitor = {
		.shared = &shared,
		.philo = philo,
	};


	for (int i = 0; i < NB_PHILO; i++)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (1);
		philo[i]->shared= &shared;
		philo[i]->state = SLEEPING;
		philo[i]->dead = 0;
		philo[i]->id = i + 1;
		philo[i]->left_fork = &forks[i];
		philo[i]->right_fork = &forks[(i + 1) % NB_PHILO];
	}

	for (int i = 0; i < NB_PHILO; i++)
	{
		shared.start_time = get_current_time();
		pthread_create(&philo[i]->thread, NULL, routine, philo[i]);
	}

	pthread_create(&monitor.thread, NULL, routine_monitor, &monitor);
	pthread_join(monitor.thread, NULL);

	clear_philo(philo);
}

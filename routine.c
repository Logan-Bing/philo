#include "header.h"

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_shared *shared = philo->shared;

	if (philo->id % 2 == 0)
		ft_usleep(shared->time_to_eat);
	while (1)
	{	
		if (!eating(philo) || !sleeping(philo) || !thinking(philo))
			break;
	}
	return (NULL);
}

void	*routine_monitor(void *arg)
{
	t_philo		**philo = (t_philo **)arg;
	t_shared	*shared = philo[0]->shared;
	int			philo_eaten;
	int i;

	philo_eaten = 0;
	while (1)
	{
		i = 0;
		while (i < NB_PHILO)
		{
			if (last_meal_elapsed_time(philo[i]) >= shared->time_to_die)
				update_shared_value(&philo[i]->dead_lock, &philo[i]->dead);
			if (read_shared_value(&philo[i]->meal_eaten_lock, &philo[i]->meal_eaten) >= shared->must_eat)
				philo_eaten++;
			if (philo_eaten == NB_PHILO)
			{
				update_shared_value(&shared->stop_lock, &shared->stop);
				break;
			}
			if (read_shared_value(&philo[i]->dead_lock, &philo[i]->dead))
			{
				update_shared_value(&shared->stop_lock, &shared->stop);
				print_action(philo[i], DEATH_STR);
				break;
			}
			i++;
		}
		if (shared->stop)
			break;
	}
	return (NULL);
}


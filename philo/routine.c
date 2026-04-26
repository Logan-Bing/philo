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
	int i;

	ft_usleep(1000);
	while (1)
	{
		i = 0;
		while (i < shared->n_philo)
		{
			if (last_meal_elapsed_time(philo[i]) >= shared->time_to_die)
				update_shared_value(&philo[i]->dead_lock, &philo[i]->dead);
			if (has_philo_finish_eaten(philo[i]))
				shared->philos_ate_count++;
			if (is_philo_dead(philo[i]) || all_philos_ate(philo[i], shared->philos_ate_count))
			{
				update_shared_value(&shared->stop_lock, &shared->stop);
				break;
			}
			i++;
		}
		if (shared->stop)
			break;
	}
	return (NULL);
}


#include "header.h"

int	clear_philo(t_philo *philo[])
{
	int	i;
	int	n_philo;

	i = 0;
	n_philo = philo[i]->shared->n_philo;
	while (i < n_philo)
	{
		if (pthread_join(philo[i]->thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

// int	clear_mutex(t_philo *philo[])
// {
//
// }

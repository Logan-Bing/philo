#include "header.h"

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

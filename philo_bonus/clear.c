#include "bonus.h"

void	clear_sem(void)
{
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_FULL);
	sem_unlink(SEM_END);
	sem_unlink(SEM_LAST_MEAL);
	sem_unlink(SEM_MEAL_EATEN);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_WAITERS);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_START);
}

int		kill_philos(t_shared *shared)
{
	int i;

	i = 0;
	while (i < shared->n_philo)
	{
		kill(shared->philo_pid[i], SIGKILL);
		waitpid(shared->philo_pid[i], NULL, 0);
		i++;
	}
	return (1);
}

#include "bonus.h"

int	print_action(struct s_philo *philo, char *action)
{
	t_shared	*shared;
	long		timestamp;

	shared = philo->shared;
	timestamp = get_current_time() - shared->start_time;
	sem_wait(shared->print);
	printf("%ld %d %s\n", timestamp, philo->id, action);
	fflush(stdout);
	// remplacer par ft_strcmp
	if (strcmp(action, DEATH_STR) != 0)
		sem_post(shared->print);
	return (1);
}

int	update_meal_eaten(t_philo *philo)
{
	sem_wait(philo->sem_meal_eaten);
	philo->meal_eaten++;
	sem_post(philo->sem_meal_eaten);
	return (1);
}

int		eating(struct s_philo *philo)
{
	t_shared 	*shared;

	shared = philo->shared;
	sem_wait(shared->waiters);
	sem_wait(shared->forks);
	print_action(philo, FORK_STR);
	sem_wait(shared->forks);
	print_action(philo, FORK_STR);
	print_action(philo, EAT_STR);
	update_meal_eaten(philo);
	update_last_meal(philo);
	ft_usleep(shared->time_to_eat);
	sem_post(shared->forks);
	sem_post(shared->forks);
	sem_post(shared->waiters);
	return (1);
}

int		sleeping(struct s_philo *philo)
{
	t_shared 	*shared;

	shared = philo->shared;
	print_action(philo, SLEEP_STR);
	ft_usleep(shared->time_to_sleep);
	return (1);
}

int		thinking(struct s_philo *philo)
{
	print_action(philo, THINK_STR);
	return (1);
}

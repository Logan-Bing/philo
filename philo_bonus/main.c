/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 09:05:22 by llugez            #+#    #+#             */
/*   Updated: 2026/05/05 09:07:28 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	init_philo(t_philo *philo, t_shared *shared)
{
	philo->shared = shared;
	philo->last_meal = 0;
	philo->meal_eaten = 0;
	philo->sem_last_meal = sem_open(SEM_LAST_MEAL, O_CREAT, 0644, 1);
	philo->sem_meal_eaten = sem_open(SEM_MEAL_EATEN, O_CREAT, 0644, 1);
}

void	philo_main(t_shared *shared)
{
	int		pid;
	t_philo	philo;
	int		i;

	i = 0;
	shared->start_time = get_current_time();
	while (i < shared->n_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philo.id = i + 1;
			init_philo(&philo, shared);
			sem_wait(shared->start);
			pthread_create(&philo.thread, NULL, local_routine, &philo);
			if (philo.id % 2 == 0)
				ft_usleep(shared->time_to_eat);
			while (eating(&philo) && sleeping(&philo) && thinking(&philo))
				;
		}
		shared->philo_pid[i] = pid;
		i++;
	}
}

void	wait_for_philo(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philo)
	{
		sem_post(shared->start);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_shared	shared;
	pthread_t	thread_death;
	pthread_t	thread_full;

	unlink_all_sem();
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
	if (shared.must_eat != -1)
		pthread_create(&thread_full, NULL, routine_full, &shared);
	sem_wait(shared.end);
	pthread_join(thread_death, NULL);
	if (shared.must_eat != -1)
		pthread_join(thread_full, NULL);
	clear_sem(&shared);
	return (0);
}

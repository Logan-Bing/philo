/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:00:53 by llugez            #+#    #+#             */
/*   Updated: 2026/05/05 09:39:49 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*routine(void *arg)
{
	t_philo		*philo;
	t_shared	*shared;

	philo = (t_philo *)arg;
	shared = philo->shared;
	if (philo->id % 2 == 0)
		ft_usleep(shared, shared->time_to_eat);
	while (1)
	{
		if (!eating(philo) || !sleeping(philo) || !thinking(philo))
			break ;
	}
	return (NULL);
}

void	check_data(t_philo *philo)
{
	t_shared	*shared;

	shared = philo->shared;
	if (last_meal_elapsed_time(philo) >= shared->time_to_die)
		update_shared_value(&philo->dead_lock, &philo->dead);
	if (has_philo_finish_eaten(philo))
		shared->ate_count++;
}

void	*routine_monitor(void *arg)
{
	t_philo		**philo;
	t_shared	*shared;
	int			i;

	philo = (t_philo **)arg;
	shared = philo[0]->shared;
	ft_usleep(shared, shared->time_to_eat - 100);
	while (1)
	{
		i = 0;
		while (i < shared->n_philo)
		{
			check_data(philo[i]);
			if (is_dead(philo[i]) || all_ate(philo[i], shared->ate_count))
			{
				update_shared_value(&shared->stop_lock, &shared->stop);
				break ;
			}
			i++;
		}
		usleep(100);
		if (shared->stop)
			break ;
	}
	return (NULL);
}

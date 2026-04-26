/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:46:58 by llugez            #+#    #+#             */
/*   Updated: 2026/04/26 16:01:42 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	print_action(struct s_philo *philo, char *action)
{
	long		timestamp;
	t_shared	*shared;

	shared = philo->shared;
	pthread_mutex_lock(&philo->shared->write_lock);
	timestamp = get_current_time() - philo->shared->start_time;
	if (read_shared_value(&shared->stop_lock, &shared->stop))
	{
		pthread_mutex_unlock(&philo->shared->write_lock);
		return (0);
	}
	printf("%ld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->shared->write_lock);
	return (1);
}

int	taking_forks(t_philo *philo)
{
	t_shared	*shared;

	shared = philo->shared;
	if (!philo->right_fork || philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, FORK_STR);
		if (shared->n_philo == 1 && !philo->right_fork)
		{
			ft_usleep(philo->shared->time_to_die);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, FORK_STR);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, FORK_STR);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, FORK_STR);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	t_shared	*shared;

	shared = philo->shared;
	if (read_shared_value(&shared->stop_lock, &shared->stop))
		return (0);
	if (!taking_forks(philo))
		return (0);
	print_action(philo, EAT_STR);
	update_last_meal(philo);
	ft_usleep(philo->shared->time_to_eat);
	update_shared_value(&philo->meal_eaten_lock, &philo->meal_eaten);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int	sleeping(struct s_philo *philo)
{
	t_shared	*shared;

	shared = philo->shared;
	if (read_shared_value(&shared->stop_lock, &shared->stop))
		return (0);
	print_action(philo, SLEEP_STR);
	ft_usleep(philo->shared->time_to_sleep);
	return (1);
}

int	thinking(struct s_philo *philo)
{
	t_shared	*shared;

	shared = philo->shared;
	if (read_shared_value(&shared->stop_lock, &shared->stop))
		return (0);
	print_action(philo, THINK_STR);
	if (shared->n_philo % 2 != 0)
		ft_usleep(100);
	return (1);
}

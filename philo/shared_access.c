/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:00:53 by llugez            #+#    #+#             */
/*   Updated: 2026/04/26 16:30:19 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_dead(t_philo *philo)
{
	if (read_shared_value(&philo->dead_lock, &philo->dead))
	{
		print_action(philo, DEATH_STR);
		return (1);
	}
	return (0);
}

int	all_ate(t_philo *philo, int philos_ate_count)
{
	t_shared	*shared;

	shared = philo->shared;
	return (shared->must_eat != -1 && philos_ate_count == shared->n_philo);
}

int	has_philo_finish_eaten(t_philo *philo)
{
	t_shared	*shared;

	shared = philo->shared;
	if (read_shared_value(&philo->meal_eaten_lock,
			&philo->meal_eaten) == shared->must_eat && !philo->finish_eat)
	{
		philo->finish_eat = 1;
		return (1);
	}
	return (0);
}

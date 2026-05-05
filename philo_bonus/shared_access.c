/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 09:11:10 by llugez            #+#    #+#             */
/*   Updated: 2026/05/05 09:11:11 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

long	last_meal_elapsed_time(t_philo *philo)
{
	long	value;
	long	timestamp;

	sem_wait(philo->sem_last_meal);
	value = philo->last_meal;
	sem_post(philo->sem_last_meal);
	timestamp = get_current_time() - philo->shared->start_time;
	return (timestamp - value);
}

int	update_last_meal(t_philo *philo)
{
	t_shared	*shared;

	shared = philo->shared;
	sem_wait(philo->sem_last_meal);
	philo->last_meal = get_current_time() - shared->start_time;
	sem_post(philo->sem_last_meal);
	return (1);
}

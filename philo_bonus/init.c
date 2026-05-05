/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 09:10:04 by llugez            #+#    #+#             */
/*   Updated: 2026/05/05 09:11:31 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	init_shared_sem(t_shared *shared)
{
	shared->start = sem_open(SEM_START, O_CREAT, 0644, 0);
	shared->dead = sem_open(SEM_DEATH, O_CREAT, 0644, 0);
	shared->end = sem_open(SEM_END, O_CREAT, 0644, 0);
	shared->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	shared->full = sem_open(SEM_FULL, O_CREAT, 0644, 0);
	if (shared->n_philo == 1)
		shared->waiters = sem_open(SEM_WAITERS, O_CREAT, 0644, 1);
	else
		shared->waiters = sem_open(SEM_WAITERS, O_CREAT, 0644, shared->n_philo
				- 1);
	shared->forks = sem_open(SEM_FORKS, O_CREAT, 0644, shared->n_philo);
	return (1);
}

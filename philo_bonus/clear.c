/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 09:11:26 by llugez            #+#    #+#             */
/*   Updated: 2026/05/05 09:11:26 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void	clear_all_sem(t_shared *shared)
{
	sem_close(shared->dead);
	sem_close(shared->full);
	sem_close(shared->end);
	sem_close(shared->print);
	sem_close(shared->waiters);
	sem_close(shared->forks);
	sem_close(shared->start);
}

void	unlink_all_sem(void)
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

void	clear_sem(t_shared *shared)
{
	clear_all_sem(shared);
	unlink_all_sem();
}

int	kill_philos(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philo)
	{
		kill(shared->philo_pid[i], SIGKILL);
		waitpid(shared->philo_pid[i], NULL, 0);
		i++;
	}
	return (1);
}

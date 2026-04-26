/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:00:53 by llugez            #+#    #+#             */
/*   Updated: 2026/04/26 16:01:43 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_valid_input(t_shared shared)
{
	return (shared.n_philo > 0 && shared.n_philo <= 200
		&& shared.time_to_die > 0 && shared.time_to_eat > 0
		&& shared.time_to_sleep > 0);
}

int	is_valid_data(t_shared *shared, int argc, char *argv[])
{
	if (!is_valid_input(*shared))
	{
		write(2, INPUT_ERROR, 23);
		return (0);
	}
	if (argc == 6)
	{
		shared->must_eat = ft_atol(argv[5]);
		if (shared->must_eat < 0)
		{
			write(2, INPUT_ERROR, 23);
			return (0);
		}
	}
	return (1);
}

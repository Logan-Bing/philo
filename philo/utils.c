/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:00:53 by llugez            #+#    #+#             */
/*   Updated: 2026/05/05 09:37:39 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(t_shared *shared, size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds
		&& !read_shared_value(&shared->stop_lock, &shared->stop))
		usleep(100);
	return (0);
}

long	last_meal_elapsed_time(t_philo *philo)
{
	long	timestamp;

	timestamp = get_current_time() - philo->shared->start_time;
	return (timestamp - read_last_meal(philo));
}

long	ft_atol(const char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (((str[i] == ' ') || (str[i] >= '\t' && str[i] <= '\r')))
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			nb *= 10;
			nb += (str[i] - '0');
			i++;
		}
		else
		{
			return (-1);
		}
	}
	if (nb > INT_MAX)
		return (-1);
	return (nb);
}

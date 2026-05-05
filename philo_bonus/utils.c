/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez </var/spool/mail/llugez>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 09:11:00 by llugez            #+#    #+#             */
/*   Updated: 2026/05/05 09:11:04 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
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

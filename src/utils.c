/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:05:22 by ekordi            #+#    #+#             */
/*   Updated: 2023/11/17 13:27:44 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	array_is_digit(char **str)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (str[i])
	{
		while (str[i][n])
		{
			if ((str[i][n] >= '0' && str[i][n] <= '9'))
				n++;
			else
			{
				ft_putstr_fd("invalid input", 2);
				exit(1);
			}
		}
		n = 0;
		i++;
	}
}

int	ft_usleep(unsigned int time)
{
	long int	start;

	start = get_timestamp();
	while (get_timestamp() - start < time)
		usleep(100);
	return (0);
}

u_int64_t	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		printf("gettime failed");
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

void	message(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_timestamp() - philo->data->start_time;
	if (philo->data->print_switch == 0)
		printf("%lld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

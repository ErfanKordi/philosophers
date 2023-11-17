/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:34:50 by ekordi            #+#    #+#             */
/*   Updated: 2023/11/17 13:27:04 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	message(RIGHTFORK, philo);
	if (philo->data->philo_num == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		ft_usleep(philo->data->death_time + 10);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	message(LEFTFORK, philo);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eating(t_philo *philo)
{
	pickup_fork(philo);
	if (philo->data->philo_num == 1)
		return ;
	message(EAT, philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->eat_count++;
	philo->last_meal = get_timestamp() - philo->data->start_time;
	pthread_mutex_unlock(&philo->philo_lock);
	ft_usleep(philo->data->eat_time);
	drop_fork(philo);
	message(SLEEP, philo);
	ft_usleep(philo->data->sleep_time);
}

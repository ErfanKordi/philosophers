/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:28:58 by ekordi            #+#    #+#             */
/*   Updated: 2023/11/17 13:28:50 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	eat_check(t_philo *philo, int i)
{
	if (philo->data->meals_num)
	{
		pthread_mutex_lock(&philo->data->philos[i].philo_lock);
		if (philo->data->philos[i].eat_count == philo->data->meals_num)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished_eating++;
			pthread_mutex_unlock(&philo->data->lock);
			philo->data->philos[i].eat_count++;
		}
		pthread_mutex_unlock(&philo->data->philos[i].philo_lock);
	}
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->finished_eating == philo->data->philo_num)
	{
		philo->data->finish = 1;
		pthread_mutex_lock(&philo->data->print);
		philo->data->print_switch = 1;
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	death_check(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->lock);
	pthread_mutex_lock(&philo->data->philos[i].philo_lock);
	if (!philo->data->death && (philo->data->philos[i].last_meal
			+ philo->data->death_time) < (get_timestamp()
			- philo->data->start_time))
	{
		message(DIE, &philo->data->philos[i]);
		pthread_mutex_unlock(&philo->data->philos[i].philo_lock);
		pthread_mutex_lock(&philo->data->print);
		philo->data->print_switch = 1;
		pthread_mutex_unlock(&philo->data->print);
		philo->data->death = 1;
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->philos[i].philo_lock);
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

void	*supervisor(void *philo_pointer)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)philo_pointer;
	while (1)
	{
		eat_check(philo, i);
		if (death_check(philo, i))
			return (NULL);
		if (i == philo->data->philo_num - 1)
			i = 0;
		else
			i++;
	}
	return (NULL);
}

void	*philosopher_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time + 1);
	while (1)
	{
		eating(philo);
		message(THINK, philo);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->death == 1 || philo->data->finish == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	return (NULL);
}

void	thread_create(t_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_create(&philo->philosopher_threads[i], NULL,
				philosopher_thread, &philo->philos[i]))
			ft_exit(philo, 0);
		i++;
	}
	if (pthread_create(&philo->supervisor, NULL, &supervisor,
			&philo->philos[0]))
		ft_exit(philo, 0);
	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_join(philo->philosopher_threads[i++], NULL))
			ft_exit(philo, 0);
	}
	if (pthread_join(philo->supervisor, NULL))
		ft_exit(philo, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:20:29 by ekordi            #+#    #+#             */
/*   Updated: 2023/10/07 13:54:50 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->leftFork);
	pthread_mutex_lock(philo->rightFork);
	usleep(1000);
	printf("philo *%d is eating\n", philo->id);
	pthread_mutex_unlock(philo->leftFork);
	pthread_mutex_unlock(philo->rightFork);
}

void	giveForks(t_data *data)
{
	int	n;

	n = 0;
	while (n < data->philoNum)
	{
		pthread_mutex_init(&data->forks[n], NULL);
		n++;
	}
	data->philos[0].leftFork = &data->forks[0];
	data->philos[0].rightFork = &data->forks[data->philoNum - 1];
	n = 1;
	while (n < data->philoNum)
	{
		data->philos[n].leftFork = &data->forks[n];
		data->philos[n].rightFork = &data->forks[(n - 1) % data->philoNum];
		n++;
	}
}

void	parsArgs(char **argv, t_data *data)
{
	int	i;

	i = 0;
	data->philoNum = ft_atoi(argv[1]);
	data->deathTime = ft_atoi(argv[2]);
	data->eatTime = ft_atoi(argv[3]);
	data->sleepTime = ft_atoi(argv[4]);
	if (argv[5])
		data->mealsNum = ft_atoi(argv[5]);
	else
		data->mealsNum = 0;
	data->forks = calloc(sizeof(pthread_mutex_t), data->philoNum);
	data->philos = calloc(sizeof(t_philo), data->philoNum);
	if (!data->philos)
		printf("error allocation");
	while (i++ < data->philoNum)
		data->philos[i].id = i;
}

void	*philosopher_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eating(philo); // Call the eating function for this philosopher
		// Implement other behavior if needed
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int			i;
	t_data		philo;
	pthread_t	philosopher_threads[philo.philoNum];

	i = 0;
	if (argc < 4)
	{
		ft_putstr_fd("too few arguments!", 2);
		exit(1);
	}
	parsArgs(argv, &philo);
	giveForks(&philo);
	for (int i = 0; i < philo.philoNum; i++)
	{
		// Pass the philosopher struct and create a separate thread for each philosopher
		pthread_create(&philosopher_threads[i], NULL, philosopher_thread,
			&philo.philos[i]);
	}
	return (0);
}

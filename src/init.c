/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:48:05 by ekordi            #+#    #+#             */
/*   Updated: 2023/11/17 13:28:35 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	give_forks(t_data *data)
{
	int	n;

	n = 0;
	while (n < data->philo_num)
		pthread_mutex_init(&data->forks[n++], NULL);
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->philo_num - 1];
	n = 1;
	while (n < data->philo_num)
	{
		data->philos[n].left_fork = &data->forks[n];
		data->philos[n].right_fork = &data->forks[(n - 1) % data->philo_num];
		n++;
	}
}

void	pars_args(char **argv, t_data *data)
{
	array_is_digit(argv);
	data->philo_num = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->meals_num = ft_atoi(argv[5]);
		if (!data->meals_num)
		{
			ft_putstr_fd("invalid input", 2);
			exit(1);
		}
	}
	if (data->philo_num == 0)
	{
		ft_putstr_fd("invalid input", 2);
		exit(1);
	}
}

void	init(t_data *data)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	data->death = 0;
	data->finish = 0;
	data->print_switch = 0;
	data->finished_eating = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->lock, NULL);
	allocation(data);
	data->start_time = get_timestamp();
	while (i < data->philo_num)
	{
		data->philos[n++].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		pthread_mutex_init(&data->philos[i++].philo_lock, NULL);
	}
}

void	allocation(t_data *data)
{
	data->forks = calloc(sizeof(pthread_mutex_t), data->philo_num);
	data->philos = calloc(sizeof(t_philo), data->philo_num);
	data->philosopher_threads = calloc(sizeof(pthread_t), data->philo_num);
	if (!data->philos || !data->forks || !data->philosopher_threads)
	{
		ft_putstr_fd("Memory allocation failed", 2);
		ft_exit(data, 1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:20:29 by ekordi            #+#    #+#             */
/*   Updated: 2023/11/17 12:01:06 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_exit(t_data *data, int error)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->lock);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->philosopher_threads)
		free(data->philosopher_threads);
	if (error)
		exit(1);
}

int	main(int argc, char **argv)
{
	t_data	philo;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Invalid number of arguments", 2);
		exit(1);
	}
	pars_args(argv, &philo);
	init(&philo);
	give_forks(&philo);
	thread_create(&philo);
	ft_exit(&philo, 0);
	return (0);
}

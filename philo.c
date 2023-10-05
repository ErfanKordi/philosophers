/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:20:29 by ekordi            #+#    #+#             */
/*   Updated: 2023/10/05 13:07:26 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 4)
	{
		ft_putstr_fd("too few arguments!", 2);
		exit(1);
	}
	int number_of_philosophers = ft_atoi(argv[1]);
	pthread_t *philo = (pthread_t*)calloc(sizeof(pthread_t), number_of_philosophers);
	int forks =  number_of_philosophers;

}

#ifndef PHILO_H
#define	PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "My_C_Library/libft.h"

typedef struct s_philo
{
	pthread_t *philo;
	int id;
	pthread_mutex_t *leftFork;
	pthread_mutex_t *rightFork;
} t_philo;

typedef struct s_data
{
	int philoNum;
	int deathTime;
	int eatTime;
	int sleepTime;
	int mealsNum;
	t_philo *philos;
	pthread_mutex_t *forks;
} t_data;


#endif

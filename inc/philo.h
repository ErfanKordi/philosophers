/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:49:12 by ekordi            #+#    #+#             */
/*   Updated: 2023/11/17 12:31:45 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define LEFTFORK "has taken a fork"
# define RIGHTFORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					eat_count;
	u_int64_t			death_time;
	u_int64_t			last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		philo_lock;
	t_data				*data;

}						t_philo;

struct					s_data
{
	pthread_t			supervisor;
	int					print_switch;
	int					philo_num;
	int					death;
	int					finish;
	int					death_time;
	int					eat_time;
	int					finished_eating;
	int					sleep_time;
	int					meals_num;
	pthread_t			*philosopher_threads;
	u_int64_t			start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		lock;
};

u_int64_t				get_timestamp(void);
void					allocation(t_data *data);
void					ft_exit(t_data *data, int error);
int						ft_atoi(const char *str);
void					array_is_digit(char **str);
int						ft_usleep(unsigned int time);
void					message(char *str, t_philo *philo);
int						ft_strcmp(char *s1, char *s2);
void					ft_putstr_fd(char *s, int fd);
void					eating(t_philo *philo);
void					*philosopher_thread(void *arg);
void					*monitor(void *philo_pointer);
void					thread_create(t_data *philo);
void					give_forks(t_data *data);
void					pars_args(char **argv, t_data *data);
void					init(t_data *table);

#endif

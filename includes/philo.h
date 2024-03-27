/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktorvi <ktorvi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:14 by vphilipp          #+#    #+#             */
/*   Updated: 2024/03/26 16:02:51 by ktorvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_chopstick
{
	pthread_mutex_t	chopstick;
	bool			failed;
	int				id;
}					t_chopstick;

typedef struct s_philo
{
	pthread_t		thread;
	bool			failed;
	_Atomic(bool) eating;
	int				id;
	_Atomic(bool) reached_max;
	int				meals_eaten;
	_Atomic(long) time_last_meal;
	_Atomic(bool) alive;
	t_chopstick		*r_chop;
	t_chopstick		*l_chop;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	long			nb_philos;
	_Atomic(long) time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	long			max_meals;
	_Atomic(bool) end;
	pthread_t		dead_thread;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	bool			failed;
	t_chopstick		**chopsticks;
	t_philo			**philos;
}					t_table;

void				*p_routine(void *arg);
void				join_philos(t_table *table);
void				*d_routine(void *arg);
bool				everyone_full(t_table *table);
void				create_threads(t_table *table);
void				lock_mtx(t_philo *philo);
void				unlock_mtx(t_philo *philo);
void				print_state(t_philo *philo, char state);
void				init(t_table *table);
t_table				*create_table(int argc, char **argv);
int					verif_table(t_table *table);
void				clear_table(t_table *table);
long				get_current_time(void);
int					verify_inputs(int argc, char **argv);
int					ft_usleep(size_t milliseconds);
int					ft_atol(const char *str);

#endif

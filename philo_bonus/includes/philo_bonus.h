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
# include <semaphore.h>
# include <signal.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_chopstick
{
	sem_t			chopstick;
	bool			failed;
	int				id;
}					t_chopstick;

typedef struct s_philo
{
	pthread_t		dead_thread;
	bool			failed;
	_Atomic(bool) eating;
	int				id;
	_Atomic(bool) reached_max;
	int				meals_eaten;
	_Atomic(long) time_last_meal;
	_Atomic(bool) alive;
	struct s_table	*table;
	long			max_meals;
	pid_t			pid;
}					t_philo;

typedef struct s_table
{
	size_t			nb_philos;
	_Atomic(long) time_to_die;
	long			max_meals;
	long			time_to_eat;
	long			time_to_sleep;
	_Atomic(long) start_time;
	sem_t			*end_sem;
	_Atomic(bool) end;
	sem_t			*dead;
	sem_t			*print;
	bool			failed;
	sem_t			*chopsticks;
	t_philo			**philos;
}					t_table;
void				kill_processes(t_table *table);

void				ft_putl(long nb);
void				print_meals(t_philo *philo);
void				init_dead_thread(t_philo *philo);
void				p_routine(t_philo *arg);
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

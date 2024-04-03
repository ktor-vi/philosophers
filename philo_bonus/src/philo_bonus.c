/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktorvi <ktorvi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:03:12 by ktorvi            #+#    #+#             */
/*   Updated: 2024/03/26 16:04:48 by ktorvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <pthread.h>
#include <stdlib.h>

void	*d_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		if ((get_current_time()
				- philo->time_last_meal) > philo->table->time_to_die
			&& !philo->reached_max)
		{
			print_state(philo, 'd');
			i = -1;
			while (++i < philo->table->nb_philos)
				sem_post(philo->table->end_sem);
			return (0);
		}
		ft_usleep(5);
	}
}

void	take_forks_and_spaghett(t_philo *philo)
{
	sem_wait(philo->table->chopsticks);
	print_state(philo, 'f');
	if (philo->table->nb_philos == 1)
		return ;
	sem_wait(philo->table->chopsticks);
	print_state(philo, 'f');
	print_state(philo, 'e');
	philo->time_last_meal = get_current_time();
	ft_usleep(philo->table->time_to_eat);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->max_meals)
	{
		philo->reached_max = true;
		sem_post(philo->table->end_sem);
	}
	sem_post(philo->table->chopsticks);
	sem_post(philo->table->chopsticks);
}

void	p_routine(t_philo *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time_last_meal = get_current_time();
	init_dead_thread(philo);
	while (!philo->reached_max)
	{
		take_forks_and_spaghett(philo);
		if (!philo->reached_max)
		{
			print_state(philo, 's');
			ft_usleep(philo->table->time_to_sleep);
			print_state(philo, 't');
		}
	}
	pthread_join(philo->dead_thread, NULL);
	exit(EXIT_SUCCESS);
}

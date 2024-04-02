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

static int	rip_in_peace(t_philo *philo)
{
	sem_wait("/dead");
	philo->alive = false;
	philo->table->end = true;
	print_state(philo, 'd');
	sem_post("/end");
	sem_post("/dead");
	return (1);
}

int	d_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_current_time()
			- philo->time_last_meal > philo->table->time_to_die
			&& !philo->eating && !philo->reached_max)
		{
			philo->alive = false; // Set alive to false first
			sem_wait("/dead");
			philo->table->end = true;
			print_state(philo, 'd');
			sem_post("/end");
			sem_post("/dead");
			return (1);
		}
		else
		{
			return (0);
		}
		ft_usleep(5);
	}
}
void	take_forks_and_spaghett(t_philo *philo)
{
	sem_wait("/chopsticks");
	print_state(philo, 'f');
	if (philo->table->nb_philos != 1)
	{
		sem_wait("/chopsticks");
		philo->eating = true;
		print_state(philo, 'f');
		print_state(philo, 'e');
		philo->meals_eaten++;
		philo->time_last_meal = get_current_time();
		if (philo->meals_eaten == philo->max_meals)
			philo->reached_max = true;
		;
		ft_usleep(philo->table->time_to_eat);
		philo->eating = false;
		sem_post("/chopsticks");
	}
	sem_post("/chopsticks");
}

void	p_routine(t_philo *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(50);
	while (!philo->table->end && !philo->reached_max)
	{
		sem_wait("/end");
		if (d_routine(philo))
			exit(EXIT_FAILURE);
		take_forks_and_spaghett(philo);
		if (!philo->table->end && philo->alive && philo->table->nb_philos != 1)
		{
			print_state(philo, 's');
			ft_usleep(philo->table->time_to_sleep);
			print_state(philo, 't');
		}
		if (d_routine(philo))
			exit(EXIT_FAILURE);
		if (philo->table->nb_philos == 1 || philo->reached_max
			|| philo->table->end)
			exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}

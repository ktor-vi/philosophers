/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:32:24 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/27 08:32:26 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

void	join_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philos)
		pthread_join(table->philos[i]->thread, NULL);
	return ;
}
void	print_state(t_philo *philo, char state)
{
	long	time;

	time = (*get_current_time)() - (philo->table->start_time);
	pthread_mutex_lock(&philo->table->print);
	if (state == 'f')
		printf("%lu %d has taken a fork\n", time, philo->id);
	if (state == 'e')
		printf("%lu %d is eating\n", time, philo->id);
	if (state == 't')
		printf("%lu %d is thinking\n", time, philo->id);
	if (state == 's')
		printf("%lu %d is sleeping\n", time, philo->id);
	if (state == 'd')
		printf("%lu %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->print);
}
void	*rip_in_peace(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead);
	philo->alive = false;
	philo->table->end = true;
	print_state(philo, 'd');
	pthread_mutex_unlock(&philo->table->dead);
	return (NULL);
}

void	take_forks_and_spaghett(t_philo *philo)
{
	long	delay;

	delay = (*get_current_time)() - philo->time_last_meal;
	pthread_mutex_lock(&philo->r_chop->chopstick);
	print_state(philo, 'f');
	if (delay > philo->table->time_to_die || !philo->l_chop)
		return ;
	pthread_mutex_lock(&philo->l_chop->chopstick);
	print_state(philo, 'f');
	print_state(philo, 'e');
	philo->time_last_meal = (*get_current_time)();
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->max_meals)
		philo->reached_max = true;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->r_chop->chopstick);
	pthread_mutex_unlock(&philo->l_chop->chopstick);
}

void	*p_routine(void *arg)
{
	t_philo	*philo;
	long	delay;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		ft_usleep(philo->table->time_to_eat / 10);
	// else
	// 	ft_usleep(philo->table->time_to_sleep);
	while (!philo->table->end && philo->alive && !philo->reached_max)
	{
		delay = (*get_current_time)() - philo->time_last_meal;
		if (delay > philo->table->time_to_die || philo->table->nb_philos == 1)
			return (rip_in_peace(philo));
		take_forks_and_spaghett(philo);
		philo->time_last_meal = (*get_current_time)();
		if (!philo->table->end)
		{
			print_state(philo, 't');
			print_state(philo, 's');
			ft_usleep(philo->table->time_to_sleep);
		}
	}
	return (NULL);
}

// void create_threads(t_table *table)
// {
// 	int i;
//
// 	i = -1;
// 	while (++i < table->nb_philos)
// 		if (pthread_create(&table->philos[i]->thread, NULL, &p_routine,
// table->philos[i]) < 0)
// 			table->philos[i]->failed = true;
// }

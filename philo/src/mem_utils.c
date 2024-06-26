/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:30:25 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/26 16:30:29 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clear_table(t_table *table)
{
	int	k;

	k = 0;
	pthread_mutex_destroy(&table->dead);
	pthread_mutex_destroy(&table->print);
	while (k < table->nb_philos)
	{
		if (table->philos && table->chopsticks && table->philos[k])
			free(table->philos[k]);
		k++;
	}
	free(table->philos);
	k = 0;
	while (k < table->nb_philos && table->chopsticks)
	{
		if (table->chopsticks[k])
		{
			pthread_mutex_destroy(&table->chopsticks[k]->chopstick);
			free(table->chopsticks[k]);
		}
		k++;
	}
	free(table->chopsticks);
	free(table);
}

int	verif_table(t_table *table)
{
	int	k;

	k = 0;
	if (!table->philos || !table->chopsticks || table->failed)
		return (1);
	while (k < table->nb_philos)
	{
		if (!table->philos[k] || table->philos[k]->failed)
			return (1);
		k++;
	}
	k = 0;
	while (k < table->nb_philos)
	{
		if (!table->chopsticks[k] || table->chopsticks[k]->failed)
			return (1);
		k++;
	}
	return (0);
}

void	lock_mtx(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_chop->chopstick);
		print_state(philo, 'f');
		if (philo->table->nb_philos != 1)
			pthread_mutex_lock(&philo->l_chop->chopstick);
	}
	else
	{
		pthread_mutex_lock(&philo->l_chop->chopstick);
		print_state(philo, 'f');
		pthread_mutex_lock(&philo->r_chop->chopstick);
	}
}

void	unlock_mtx(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (philo->table->nb_philos != 1)
			pthread_mutex_unlock(&philo->l_chop->chopstick);
		pthread_mutex_unlock(&philo->r_chop->chopstick);
	}
	else
	{
		pthread_mutex_unlock(&philo->r_chop->chopstick);
		pthread_mutex_unlock(&philo->l_chop->chopstick);
	}
}

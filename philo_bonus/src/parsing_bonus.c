/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktorvi <ktorvi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:03:05 by ktorvi            #+#    #+#             */
/*   Updated: 2024/03/26 16:03:06 by ktorvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <unistd.h>

void	init_dead_thread(t_philo *philo)
{
	if (pthread_create(&philo->dead_thread, NULL, &d_routine, philo) < 0)
		philo->table->failed = true;
}
t_philo	**init_philos(t_table *table)
{
	int		i;
	t_philo	**philos;

	philos = malloc(table->nb_philos * sizeof(t_philo *));
	if (!philos)
		table->failed = true;
	i = -1;
	while (++i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			table->failed = true;
		philos[i]->id = i + 1;
		philos[i]->alive = true;
		philos[i]->max_meals = table->max_meals;
		philos[i]->reached_max = false;
		philos[i]->meals_eaten = 0;
		philos[i]->table = table;
	}
	return (philos);
}

t_table	*create_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	if (argc == 6)
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = LONG_MAX;
	table->nb_philos = (size_t)ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->end = false;
	return (table);
}

void	init(t_table *table)
{
	int	i;

	i = -1;
	table->failed = false;
	table->start_time = (*get_current_time)();
	table->philos = init_philos(table);
	table->chopsticks = sem_open("/chopsticks", O_CREAT, 0644,
			table->nb_philos);
	if (table->chopsticks == SEM_FAILED)
		table->failed = true;
	table->dead = sem_open("/dead", O_CREAT, 0644, 1);
	if (table->dead == SEM_FAILED)
		table->failed = true;
	table->print = sem_open("/print", O_CREAT, 0644, 1);
	if (table->print == SEM_FAILED)
		table->failed = true;
	table->end_sem = sem_open("/end", O_CREAT, 0644, 0);
	if (table->end_sem == SEM_FAILED)
		table->failed = true;
	if (table->failed)
	{
		clear_table(table);
		exit(1);
	}
}

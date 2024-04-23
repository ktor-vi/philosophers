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

#include "../includes/philo.h"
#include <unistd.h>

void	init_dead_thread(t_table *table)
{
	if (pthread_create(&table->dead_thread, NULL, &d_routine, table) < 0)
		table->failed = true;
}

t_philo	**init_philos(t_table *table)
{
	int		i;
	t_philo	**philos;

	i = -1;
	philos = malloc(table->nb_philos * sizeof(t_philo *));
	while (++i < table->nb_philos && table->chopsticks)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos || !philos[i])
			return (philos);
		philos[i]->id = i + 1i;
		philos[i]->alive = true;
		philos[i]->failed = false;
		philos[i]->eating = false;
		philos[i]->reached_max = false;
		philos[i]->meals_eaten = 0;
		philos[i]->time_last_meal = get_current_time();
		philos[i]->r_chop = table->chopsticks[i];
		if (i == 0)
			philos[i]->l_chop = table->chopsticks[table->nb_philos - 1];
		else
			philos[i]->l_chop = table->chopsticks[i - 1];
		philos[i]->table = table;
	}
	return (philos);
}

t_chopstick	**init_chopsticks(t_table *table)
{
	int			i;
	t_chopstick	**chopsticks;

	i = 0;
	chopsticks = malloc(table->nb_philos * sizeof(t_chopstick *));
	while (i < table->nb_philos)
	{
		chopsticks[i] = malloc(sizeof(t_chopstick));
		if (!chopsticks || !chopsticks[i])
			return (chopsticks);
		chopsticks[i]->id = i;
		chopsticks[i]->failed = false;
		if (pthread_mutex_init(&chopsticks[i]->chopstick, NULL) < 0)
			chopsticks[i]->failed = true;
		i++;
	}
	return (chopsticks);
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
	table->nb_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->end = false;
	return (table);
}

int	init(t_table *table)
{
	int	i;

	i = -1;
	table->failed = false;
	table->start_time = (*get_current_time)();
	table->chopsticks = init_chopsticks(table);
	table->philos = init_philos(table);
	if (pthread_mutex_init(&table->dead, NULL) < 0)
		table->failed = true;
	if (pthread_mutex_init(&table->print, NULL) < 0)
		table->failed = true;
	while (table->philos && table && table->chopsticks
		&& ++i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, &p_routine,
				table->philos[i]) < 0)
			table->philos[i]->failed = true;
	}
	if (table && table->philos && table->chopsticks)
		init_dead_thread(table);
	if (verif_table(table) && table && table->philos && table->chopsticks)
		return (clear_table(table));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:39:04 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/26 20:33:10 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>

int	verify_inputs(int argc, char **argv)
{
	if (!(argc == 6 || argc == 5))
		return (printf("Invalid arguments.\n"), 1);
	if (ft_atol(argv[1]) > 200)
		return (printf("Too many philosophers.\n"), 1);
	if (ft_atol(argv[1]) <= 0 || ft_atol(argv[2]) <= 0 || ft_atol(argv[3]) <= 0
		|| ft_atol(argv[4]) <= 0)
		return (printf("All arguments must be positive.\n"), 1);
	if (argc == 6)
	{
		if (ft_atol(argv[5]) <= 0)
			return (printf("All arguments must be positive.\n"), 1);
	}
	return (0);
}

t_philo	**init_philos(t_table *table)
{
	int		i;
	t_philo	**philos;

	i = -1;
	philos = malloc(table->nb_philos * sizeof(t_philo *));
	while (++i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos || !philos[i])
			return (philos);
		philos[i]->id = i;
		philos[i]->alive = true;
		philos[i]->failed = false;
		philos[i]->reached_max = false;
		philos[i]->meals_eaten = 0;
		philos[i]->time_last_meal = (*get_current_time)() - table->time_to_eat;
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

void	init(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = (*get_current_time)();
	table->chopsticks = init_chopsticks(table);
	table->philos = init_philos(table);
	while (++i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, &p_routine,
				table->philos[i]) < 0)
			table->philos[i]->failed = true;
	}
	table->failed = false;
	if (pthread_mutex_init(&table->dead, NULL) < 0)
		table->failed = true;
	if (pthread_mutex_init(&table->print, NULL) < 0)
		table->failed = true;
	if (verif_table(table))
	{
		clear_table(table);
		exit(1);
	}
}

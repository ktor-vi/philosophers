/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:17:58 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/26 16:36:21 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <pthread.h>
#include <unistd.h>

void	run(t_table *table)
{
	size_t	i;

	i = -1;
	if (!table || !table->philos)
		exit(1);
	while (++i < table->nb_philos)
	{
		if (!table->philos[i])
			exit(1);
		table->philos[i]->pid = fork();
		if (table->philos[i]->pid == -1)
			table->failed = true;
		else if (table->philos[i]->pid == 0)
			p_routine(table->philos[i]);
		ft_usleep(50);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	if (verify_inputs(argc, argv))
		exit(1);
	table = create_table(argc, argv);
	init(table);
	run(table);
	i = -1;
	while (++i < table->nb_philos)
	{
		table->failed = true;
		table->philos[i]->failed = true;
		sem_wait(table->end_sem);
	}
	kill_processes(table);
	unlink_sems(table);
	return (0);
}

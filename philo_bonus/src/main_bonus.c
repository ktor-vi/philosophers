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
	// init_dead_thread(table);
	while (++i < table->nb_philos)
	{
		table->philos[i]->pid = fork();
		if (table->philos[i]->pid == -1)
			table->failed = true;
		else if (table->philos[i]->pid == 0)
			p_routine(table->philos[i]);
	}
	i = -1;
	while (++i < table->nb_philos)
		waitpid(table->philos[i]->pid, NULL, 0);
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
	pthread_join(table->dead_thread, NULL);
	clear_table(table);
	return (0);
}

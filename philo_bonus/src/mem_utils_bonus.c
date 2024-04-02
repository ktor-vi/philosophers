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

#include "../includes/philo_bonus.h"

void	clear_table(t_table *table)
{
	int	k;

	sem_unlink("/chopsticks");
	sem_unlink("/dead");
	sem_unlink("/print");
	sem_unlink("/end");
	sem_close(table->end_sem);
	sem_close(table->chopsticks);
	k = 0;
	while (k < table->nb_philos)
	{
		if (table->philos[k])
			free(table->philos[k]);
		k++;
	}
	free(table->philos);
	k = 0;
	sem_close(table->dead);
	sem_close(table->print);
	free(table);
}

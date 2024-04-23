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

#include "../includes/philo.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_table	*table;

	if (verify_inputs(argc, argv))
		return (1);
	table = create_table(argc, argv);
	if (init(table))
		return (1);
	join_philos(table);
	if (table && table->philos)
		clear_table(table);
	return (0);
}

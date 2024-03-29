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
		exit(1);
	table = create_table(argc, argv);
	init(table);
	join_philos(table);
	clear_table(table);
	return (0);
}

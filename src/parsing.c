/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:39:04 by vphilipp          #+#    #+#             */
/*   Updated: 2023/11/20 13:39:06 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>

void	clear_tab(char **splitted)
{
	int	k;

	k = 0;
	while (splitted[k])
	{
		free(splitted[k]);
		k++;
	}
	free(splitted);
}

t_table	*create_table(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table *));
	(void)argv;
	if (argc != 5)
		return (NULL);

		return(table);
}

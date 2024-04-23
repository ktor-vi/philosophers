/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktorvi <ktorvi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:00:49 by ktorvi            #+#    #+#             */
/*   Updated: 2024/03/26 16:00:51 by ktorvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	ft_putchar(char a)
{
	write(1, &a, 1);
}

static void	write_zeros(long nb)
{
	int	digits;

	digits = 7;
	while (nb >= 10)
	{
		nb /= 10;
		digits--;
	}
	while (digits-- > 0)
		write(1, "0", 1);
}

void	ft_putl(long nb)
{
	if (nb == LONG_MIN)
	{
		ft_putchar('-');
		ft_putchar('9');
		nb = 223372036854775807;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb < 10)
	{
		ft_putchar(nb + 48);
		return ;
	}
	else
		ft_putl(nb / 10);
	ft_putl(nb % 10);
}

void	print_state(t_philo *philo, char state)
{
	long	time;
	char	*out;

	out = NULL;
	time = (*get_current_time)() - (philo->table->start_time);
	sem_wait(philo->table->print);
	if (state == 'f')
		out = MAGENTA "has taken a fork" RESET;
	else if (state == 'e')
		out = GREEN "is eating" RESET;
	else if (state == 't')
		out = YELLOW "is thinking" RESET;
	else if (state == 's')
		out = BLUE "is sleeping" RESET;
	else if (state == 'd')
		out = RED "died" RESET;
	if (!philo->failed && !philo->table->failed)
		printf("%08lu %i %s\n", time, philo->id, out);
	sem_post(philo->table->print);
}

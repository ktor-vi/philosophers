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

#include "../includes/philo.h"

static void	ft_putchar(char a)
{
	write(1, &a, 1);
}

static void	ft_putl(long nb)
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

static void	write_time_id(long nb, t_philo *philo)
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
	ft_putl((*get_current_time)() - (philo->table->start_time));
	write(1, " ", 1);
	ft_putl(philo->id);
}

void	print_state(t_philo *philo, char state)
{
	pthread_mutex_lock(&philo->table->print);
	if (!philo->table->end)
	{
		write_time_id((*get_current_time)() - (philo->table->start_time),
			philo);
		if (state == 'f')
			write(1, " \033[34mhas taken a fork\n\033[0m", 28);
		if (state == 'e')
			write(1, " \033[32mis eating\n\033[0m", 16);
		if (state == 't')
			write(1, " \033[33mis thinking\n\033[0m", 18);
		if (state == 's')
			write(1, " \033[35mis sleeping\n\033[0m", 18);
	}
	if (state == 'd')
	{
		write_time_id((*get_current_time)() - (philo->table->start_time),
			philo);
		write(1, " \033[31mdied\n\033[0m", 11);
	}
	write(1, "\033[0m", 4);
	pthread_mutex_unlock(&philo->table->print);
}

void	print_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	write(1, "philo : ", 8);
	ft_putl(philo->id);
	write(1, "  meals : ", 10);
	ft_putl(philo->meals_eaten);
	write(1, "  max : ", 9);
	if (philo->reached_max == false)
	{
		write(1, "false\n", 6);
	}
	else
	{
		write(1, "true\n", 5);
	}
	pthread_mutex_unlock(&philo->table->print);
}

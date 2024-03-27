/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktorvi <ktorvi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:32:39 by vphilipp          #+#    #+#             */
/*   Updated: 2024/03/26 16:06:44 by ktorvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int verify_inputs(int argc, char **argv) {
  if (!(argc == 6 || argc == 5))
    return (printf("Invalid arguments.\n"), 1);
  if (ft_atol(argv[1]) > 1000)
    return (printf("Too many philosophers.\n"), 1);
  if (ft_atol(argv[1]) <= 0 || ft_atol(argv[2]) <= 0 || ft_atol(argv[3]) <= 0 ||
      ft_atol(argv[4]) <= 0)
    return (printf("All arguments must be positive.\n"), 1);
  if (argc == 6) {
    if (ft_atol(argv[5]) <= 0)
      return (printf("All arguments must be positive.\n"), 1);
  }
  return (0);
}

int ft_usleep(size_t milliseconds) {
  size_t start;

  start = get_current_time();
  while ((get_current_time() - start) < milliseconds)
    usleep(1000);
  return (0);
}

long get_current_time(void) {
  struct timeval time;

  if (gettimeofday(&time, NULL) == -1)
    write(2, "gettimeofday() error\n", 22);
  return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_atol(const char *str) {
  long result;
  int i;
  int sign;

  result = 0;
  i = 0;
  sign = 1;
  while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
    i++;
  if (str[i] == '-' || str[i] == '+') {
    if (str[i] == '-')
      sign = -1;
    i++;
  }
  if (!(str[i] >= '0' && str[i] <= '9'))
    return (0);
  while (str[i] >= '0' && str[i] <= '9') {
    result = result * 10 + (str[i++] - '0');
  }
  return (result * sign);
}

bool everyone_full(t_table *table) {
  int i;

  i = -1;
  while (++i < table->nb_philos) {
    if (table->philos[i]->reached_max && i < table->nb_philos - 1)
      continue;
    else if (table->philos[i]->reached_max && i == table->nb_philos - 1)
      return (true);
    else
      break;
  }
  return (false);
}

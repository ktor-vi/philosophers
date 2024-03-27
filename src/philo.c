  /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktorvi <ktorvi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:03:12 by ktorvi            #+#    #+#             */
/*   Updated: 2024/03/26 16:04:48 by ktorvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

void join_philos(t_table *table) {
  int i;

  i = -1;
  while (++i < table->nb_philos)
    pthread_join(table->philos[i]->thread, NULL);
  pthread_join(table->dead_thread, NULL);
  return;
}

static void *rip_in_peace(t_philo *philo) {
  pthread_mutex_lock(&philo->table->dead);
  philo->alive = false;
  philo->table->end = true;
  print_state(philo, 'd');
  pthread_mutex_unlock(&philo->table->dead);
  return (NULL);
}

void *d_routine(void *arg) {
  int i;
  t_table *table;

  table = (t_table *)arg;
  while (1) {
    i = -1;
    while (++i < table->nb_philos) {
      if (get_current_time() - table->philos[i]->time_last_meal >
              table->time_to_die &&
          !table->philos[i]->eating && !table->philos[i]->reached_max) {
        return (rip_in_peace(table->philos[i]));
      }
    }
    if (everyone_full(table))
      return (0);
        ft_usleep(5);
    }

}

void take_forks_and_spaghett(t_philo *philo) 
{
  
if(philo->id % 2 == 0)
  {
    pthread_mutex_lock(&philo->r_chop->chopstick);
  pthread_mutex_lock(&philo->l_chop->chopstick);
  }
  else
  {
    pthread_mutex_lock(&philo->l_chop->chopstick);
        pthread_mutex_lock(&philo->r_chop->chopstick);
  }
  philo->eating = true;
  print_state(philo, 'f');
  print_state(philo, 'e');
  philo->meals_eaten++;
  if (philo->meals_eaten == philo->table->max_meals)
    philo->reached_max = true;
philo->time_last_meal = get_current_time();
 
  ft_usleep(philo->table->time_to_eat);
    if(philo->id % 2 == 1)
  {
    pthread_mutex_unlock(&philo->r_chop->chopstick);
  pthread_mutex_unlock(&philo->l_chop->chopstick);
  }
  else
    {
    pthread_mutex_unlock(&philo->l_chop->chopstick);
        pthread_mutex_unlock(&philo->r_chop->chopstick);
  }
  philo->eating = false;
}

void *p_routine(void *arg) {
  t_philo *philo;

  philo = (t_philo *)arg;
  if (philo->id % 2 == 1)
    ft_usleep(10);
        while (!philo->table->end && philo->alive && !philo->reached_max) {
    take_forks_and_spaghett(philo);
    if (!philo->table->end && philo->alive && philo->table->nb_philos != 1) {
      print_state(philo, 's');
      ft_usleep(philo->table->time_to_sleep);
      print_state(philo, 't');
    }
    if (philo->table->nb_philos == 1 || philo->reached_max)
      return (NULL);
  }
  return (NULL);
}

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
typedef struct s_philosopher
{
	int			id;
	pthread_t	thread;
	// Add other necessary fields
}				t_philosopher;

typedef struct s_chopstick
{
	int			id;
	pthread_t	thread;
	// Add other necessary fields
}				t_chopstick;

typedef struct s_table
{
	int total;
	int time_die;
	int time_eat;
	int time_sleep;
	t_philosopher philosophers[];
	// Add other necessary fields
}				t_table;
// Add other necessary structures

// Function prototypes
void			*philosopher_routine(void *arg);
t_table *create_table(int argc, char **argv);
#endif

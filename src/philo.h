/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:13:55 by juportie          #+#    #+#             */
/*   Updated: 2025/07/02 11:13:27 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>


# ifndef DEBUG
#  define DEBUG 0
# endif
# define DBG_MAIN 0
# define DBG_TIME 0
# define DBG_SIM 0
# define DBG_FORK 1
# define DBG_ROUTINE 1

# define ERROR -1
# define UNSET -2

# define DEAD_CHECK_FREQ 1000
# define THINKING_PADDING 100

typedef enum e_death_state
{
	alive,
	dead
}	t_death_state;

typedef struct s_death
{
	pthread_mutex_t mutex;
	t_death_state	state;
}	t_death;

typedef struct s_shared
{
	int					philos_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_nbr;
	unsigned long long	start_time;
	t_death				death;
	pthread_mutex_t		printf_mutex;
	pthread_mutex_t		block_mutex;
}	t_shared;

typedef enum e_fork_state
{
	available,
	locked
}	t_fork_state;

typedef struct s_fork
{
	pthread_mutex_t mutex;
	t_fork_state	state;
}	t_fork;

typedef struct s_philo
{
	int					id;
	int					first_philo;// USELESS ?
	t_fork 				*forks;
	int					owned_forks[2];
	int					meals_taken;
	unsigned long long	last_meal;
	t_shared	*shared;
}	t_philo;

// error.c
int	print_err(char *msg);
// time.c
unsigned long long	get_time();
unsigned long long	get_elapsed_time_us(unsigned long long ref);// UNUSED FUNCTION ?
unsigned long long	get_elapsed_time_ms(unsigned long long ref);
// utils.c
int	is_even(int i);
int	calc_last_philo(int first, int philos_nbr);
int	is_last_philo(t_philo *philo);
// deinit.c
int	deinit_shared_mutexes(t_shared *shared);
int	free_forks(t_fork *forks, int philos_nbr);
// parsing.c
int	init_shared(t_shared *shared, int argc, char *argv[]);
// print.c
int	print_timestamp(char *str, t_philo *philo);
// threads_init.c
int	alloc_threads(pthread_t **threads, int philos_nbr);
int	init_threads(
	pthread_t *threads,
	t_philo *philos,
	int philos_nbr);
// routine_fork_utils.c
int calc_first_fork(int philo_id, int philos_nbr);
int calc_second_fork(int philo_id, int philos_nbr);
// routine_fork_take.c
t_fork	*right_fork(t_philo *philo);
t_fork	*left_fork(t_philo *philo);
int	try_take_fork(t_fork *fork, t_philo *philo, int side);
int	release_forks(t_philo *philo);
// routine_utils.c
int	set_death(t_death *death, t_philo *philo);
int	death_happened(t_death *death);
int	reached_time(unsigned long long start_time, int time);
int	eaten_enough_meals(t_philo *philo);
// routine.c
void	*routine(void *philo_struct);

#endif

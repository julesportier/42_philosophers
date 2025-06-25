/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:13:55 by juportie          #+#    #+#             */
/*   Updated: 2025/06/30 15:04:47 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>


# ifndef DEBUG
#  define DEBUG 0
# endif
# define DBG_MAIN 1
# define DBG_TIME 1
# define DBG_SIM 1

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

typedef struct s_settings
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosophers_must_eat;
	unsigned long long	start_time;
	t_death				death;
}	t_settings;

// USELESS ?
// typedef enum e_philo_state
// {
// 	// dead,
// 	sleeping,
// 	eating,
// 	thinking,
// }	t_philo_state;

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

// typedef enum e_owned_forks
// {
// 	right_fork,
// 	left_fork
// }	t_owned_forks;

typedef struct s_philo
{
	int					id;
	int					first_philo;
	// t_philo_state		state;
	t_fork 				*forks;
	// t_owned_forks		own;
	// ADD A MEMBER TO KNOW OWNED FORKS ?
	int					meals_taken;
	unsigned long long	last_meal;
	const t_settings	*settings;
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
// parsing.c
int	init_settings(t_settings *settings, int argc, char *argv[]);
// print.c
void	print_timestamp(char *str, t_philo *philo);
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
int	take_forks(t_fork *first_fork, t_fork *second_fork);
int	release_forks(t_fork *first_fork, t_fork *second_fork);
// routine.c
void	*routine(void *philo_struct);

#endif

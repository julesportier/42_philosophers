/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:13:55 by juportie          #+#    #+#             */
/*   Updated: 2025/07/09 11:00:14 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define ERROR -1
# define UNSET -2
# define SIM_END 1
# define WAIT_TIME 500

typedef enum e_sim_state
{
	running,
	stop
}	t_sim_state;

typedef struct s_sim
{
	pthread_mutex_t	mutex;
	t_sim_state		state;
}	t_sim;

typedef struct s_parameters
{
	int					philos_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_nbr;
	unsigned long long	start_time;
	t_sim				sim;
}	t_parameters;

typedef enum e_fork_state
{
	available,
	locked
}	t_fork_state;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	t_fork_state	state;
}	t_fork;

typedef struct s_meal
{
	pthread_mutex_t		mutex;
	unsigned long long	last;
	int					done;
}	t_meal;

typedef struct s_philo
{
	int					id;
	t_fork				*forks;
	int					owned_forks[2];
	t_meal				meals;
	t_parameters		*parameters;
}	t_philo;

// error.c
int					print_err(char *msg);
// time.c
unsigned long long	get_time(void);
unsigned long long	get_elapsed_time_ms(unsigned long long ref);
// deinit.c
int					deinit_sim_mutex(t_parameters *parameters);
int					free_forks(t_fork *forks, int philos_nbr);
int					free_philos(t_philo *philos, int philos_nbr);
int					free_all(
						t_parameters *parameters,
						t_fork *forks,
						t_philo *philos,
						int error);
// parsing.c
int					init_parameters(
						t_parameters *parameters,
						int argc, char
						*argv[]);
// print.c
void				print_timestamp(char *str, t_philo *philo);
void				print_death_timestamp(t_philo *philo);
// start_simulation.c
int					start_simulation(t_parameters *parameters, t_philo *philos);
// monitor.c
void				*routine_monitor(void *all_philos);
// routine_fork_take.c
t_fork				*right_fork(t_philo *philo);
t_fork				*left_fork(t_philo *philo);
void				try_take_fork(t_fork *fork, t_philo *philo, int side);
void				release_forks(t_philo *philo);
// routine_utils.c
int					is_even(int i);
int					is_sim_end(t_sim *sim);
int					reached_time(unsigned long long start_time, int time);
void				increment_meals(t_philo *philo);
void				init_last_meal(t_philo *philo);
// routine.c
void				*routine(void *philo_struct);

#endif

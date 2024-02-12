/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:55:51 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/12 12:56:23 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
//# include <_types.h>

# define ALIVE_STATE	1
# define DEAD_STATE		0

# define STATE_EATING	1
# define STATE_THINKING	2
# define STATE_SLEEPING	3

struct s_god;

typedef struct s_philo
{
	struct s_god	*god;
	pthread_t		thread;
	int				id;
	int				state;

	int				loop_count;
	int				loops;

	struct s_philo	*r_philo;
	struct s_philo	*l_philo;

	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;

	long long int	start_time;
	long long int	die_val;
	long long int	die_timer;
	long long int	eat_timer;
	long long int	sleep_timer;
}	t_philo;

typedef struct s_god
{
	pthread_mutex_t	*print_mutex;
	pthread_t		thread;
	int				philo_num;
	int				die_timer;
	int				eat_timer;
	int				sleep_timer;
	int				loops;
	struct s_philo	*philos;
}	t_god;

//time
long long int	get_time(void);

//init
int	initialize(t_philo **philo, t_god *god);
int	init_vals(int argc, char **argv, t_god *god);

//funcs
void	*philo_loop(void *philo);

//aux
long long int	get_time(void);
int				ft_usleep(long long int milliseconds);
void			print_state(int state, t_philo philo);
void			print_result(t_god *god, t_philo *philo, int state);

//free
void	free_philos(t_god *god);

#endif
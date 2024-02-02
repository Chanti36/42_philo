/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:55:51 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/02 10:25:18 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <_types.h>

# define ALIVE_STATE	0
# define DEAD_STATE		1

typedef struct s_philo
{
	//t_god			*god;
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

//free
void	free_philos(t_god *god);

#endif
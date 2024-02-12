/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:29:56 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/12 12:01:42 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_think(t_philo *philo)
{
	print_state(STATE_THINKING, *philo);
}

static void	do_eat(t_philo *philo)
{
	long long int	enter_eat_time;

	enter_eat_time = get_time();
	////printf("die timer = %lld\n",philo->die_timer);

	////lock forks
	//pthread_mutex_lock(philo->r_fork);
	//pthread_mutex_lock(philo->l_fork);
	enter_eat_time = get_time() - enter_eat_time;
	////if (enter_eat_time < philo->eat_timer)
	////	enter_eat_time = 0;

	//usleep
	//print_state(STATE_EATING, *philo);

	//philo->loop_count++;
	ft_usleep(philo->eat_timer);
	//philo->die_timer -= philo->eat_timer - enter_eat_time;
	//if (philo->die_timer > 0)
	//	philo->die_timer = philo->die_val;

	////unlock forks
	//pthread_mutex_unlock(philo->l_fork);
	//pthread_mutex_unlock(philo->r_fork);
}

static void	do_sleep(t_philo *philo)
{
	//print_state(STATE_SLEEPING, *philo);
	usleep((useconds_t)philo->sleep_timer);
	philo->die_timer -= philo->sleep_timer;
}

void	*philo_loop(void *philo)
{
	t_philo	*loop_philo;

	loop_philo = (t_philo *)philo;
	loop_philo->start_time = get_time();
	while (loop_philo->state)
	{
		if (loop_philo->state != DEAD_STATE)
			do_think(loop_philo);
		else
			return (printf("%d	DEAD\n", loop_philo->id), NULL);
		if (loop_philo->state != DEAD_STATE)
			do_eat(loop_philo);
		else
			return (printf("%d	DEAD\n", loop_philo->id), NULL);
		if (loop_philo->state != DEAD_STATE)
			do_sleep(loop_philo);
		else
			return (printf("%d	DEAD\n", loop_philo->id), NULL);
	}
	return (printf("%d	DEAD_\n", loop_philo->id), NULL);
}

/*
·	quitar tiempo de espera para el tenedor??
*/
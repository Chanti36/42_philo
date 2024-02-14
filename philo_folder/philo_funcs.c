/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:29:56 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/14 15:44:07 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_think(t_philo *philo)
{
	print_state(STATE_THINKING, philo);
}

static void	eat_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->timer_mutex);
	philo->last_eat_time = get_time() - philo->god->start_time;
	pthread_mutex_unlock(&philo->timer_mutex);
	print_state(STATE_EATING, philo);
	ft_usleep(philo->god->eat_timer);
	philo->loop_count++;
	pthread_mutex_lock(&philo->timer_mutex);
	philo->last_eat_time = get_time() - philo->god->start_time;
	pthread_mutex_unlock(&philo->timer_mutex);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

static void	do_eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_fork(philo);
		pthread_mutex_lock(&philo->r_fork);
		print_fork(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork);
		print_fork(philo);
		pthread_mutex_lock(philo->l_fork);
		print_fork(philo);
	}
	eat_time(philo);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
}

static void	do_sleep(t_philo *philo)
{
	print_state(STATE_SLEEPING, philo);
	usleep((useconds_t)philo->god->sleep_timer);
}

void	*philo_loop(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	pthread_mutex_lock(&philo->god->simulation_mutex);
	pthread_mutex_unlock(&philo->god->simulation_mutex);
	ft_usleep(philo->id);
	while (check_state(philo) != DEAD_STATE)
	{
		if (check_state(philo) != DEAD_STATE)
			do_think(philo);
		else
			return (NULL);
		if (check_state(philo) != DEAD_STATE)
			do_eat(philo);
		else
			return (NULL);
		if (check_state(philo) != DEAD_STATE)
			do_sleep(philo);
		else
			return (NULL);
	}
	return (NULL);
}

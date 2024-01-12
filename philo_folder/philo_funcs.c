/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:29:56 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/12 15:13:43 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettime() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
static int	ft_usleep(long long int milliseconds)
{
	long long int	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

static void	do_think(t_philo *philo)
{
	printf("%lld: 🤔 - philo %d - began thinking\n", \
	get_time() - philo->start_time, philo->id);
}

static void	do_eat(t_philo *philo)
{
	long long int	enter_eat_time;

	enter_eat_time = get_time();
	//printf("die timer = %lld\n",philo->die_timer);
	//lock forks
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	enter_eat_time = get_time() - enter_eat_time;
	//if (enter_eat_time < philo->eat_timer)
	//	enter_eat_time = 0;
	//usleep
	printf("%lld: 😋 - philo %d - began eating\n", \
	get_time() - philo->start_time, philo->id);
	philo->loop_count++;
	ft_usleep(philo->eat_timer);
	philo->die_timer -= philo->eat_timer - enter_eat_time;
	if (philo->die_timer > 0)
		philo->die_timer = philo->die_val;
	//unlock forks
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
}

static void	do_sleep(t_philo *philo)
{
	printf("%lld: 😴 - philo %d - began sleeping\n", \
	get_time() - philo->start_time, philo->id);
	usleep((useconds_t)philo->sleep_timer);
	philo->die_timer -= philo->sleep_timer;
}

void	*philo_loop(void *philo)
{
	t_philo	*loop_philo;

	loop_philo = (t_philo *)philo;
	((t_philo *)philo)->start_time = get_time();
	while (loop_philo->state != DEAD_STATE)
	{
		if (loop_philo->state != DEAD_STATE)
			do_think((t_philo *)philo);
		else
			return (printf("%d	DEAD\n", ((t_philo *)philo)->id), NULL);
		if (loop_philo->state != DEAD_STATE)
			do_eat((t_philo *)philo);
		else
			return (printf("%d	DEAD\n", ((t_philo *)philo)->id), NULL);
		if (loop_philo->state != DEAD_STATE)
			do_sleep((t_philo *)philo);
		else
			return (printf("%d	DEAD\n", ((t_philo *)philo)->id), NULL);
	}
	return (printf("%d	DEAD_\n", ((t_philo *)philo)->id), NULL);
}
/*
quitar tiempo de espera para el tenedor??

*/
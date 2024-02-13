/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:29:56 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/13 13:08:55 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_think(t_philo *philo)
{
	print_state(STATE_THINKING, *philo);
}

static void	do_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(philo->l_fork);

	print_state(STATE_EATING, *philo);

	philo->loop_count++;
	ft_usleep(philo->eat_timer);

	pthread_mutex_lock(&philo->god->timer_mutex);
	philo->die_timer = philo->die_val;
	pthread_mutex_unlock(&philo->god->timer_mutex);	


	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

static void	do_sleep(t_philo *philo)
{
	print_state(STATE_SLEEPING, *philo);
	usleep((useconds_t)philo->sleep_timer);
}

void	*philo_loop(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->start_time = get_time();
	pthread_mutex_lock(&philo->god->alive_mutex);
	pthread_mutex_unlock(&philo->god->alive_mutex);
	while (philo->state)
	{
		if (philo->state != DEAD_STATE)
			do_think(philo);
		else
			return (NULL);
		if (philo->state != DEAD_STATE)
			do_eat(philo);
		else
			return (NULL);
		if (philo->state != DEAD_STATE)
			do_sleep(philo);
		else
			return (NULL);
	}
	return (NULL);
}

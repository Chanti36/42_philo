/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:41:29 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/14 16:03:52 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->alive_mutex);
	state = philo->state;
	pthread_mutex_unlock(&philo->alive_mutex);
	return (state);
}

static void	*end_philos(void *god)
{
	int	i;

	i = 0;
	while (i < ((t_god *)god)->philo_num)
	{
		pthread_mutex_lock(&((t_god *)god)->philos->alive_mutex);
		((t_god *)god)->philos->state = DEAD_STATE;
		pthread_mutex_unlock(&((t_god *)god)->philos->alive_mutex);
		((t_god *)god)->philos = ((t_god *)god)->philos->r_philo;
		++i;
	}
	return (NULL);
}

static int	all_eaten(t_god *god, int result)
{
	if (result == 1)
	{
		end_philos(god);
		print_result(god, god->philos, 1);
		return (1);
	}
	return (0);
}

int	check_end(t_god *god)
{
	int		id;
	t_philo	*philo;
	int		result;

	id = god->philos->id;
	philo = god->philos->r_philo;
	result = 1;
	while (philo->id != id)
	{
		if (get_time() - philo->god->start_time - philo->last_eat_time > \
		philo->god->die_timer)
		{
			end_philos(god);
			print_result(god, philo, 0);
			return (-1);
		}
		if (((t_god *)god)->loops <= 0 || philo->loop_count < \
		((t_god *)god)->loops)
			result = 0;
		philo = philo->r_philo;
	}
	return (all_eaten(god, result));
}

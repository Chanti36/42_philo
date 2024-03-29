/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:53:41 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/14 11:15:46 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_god *god)
{
	t_philo	*free_philo;
	int		i;

	i = 0;
	while (i < god->philo_num)
	{
		free_philo = god->philos;
		if (free_philo)
		{
			pthread_mutex_destroy(&free_philo->r_fork);
			pthread_mutex_destroy(&free_philo->timer_mutex);
			pthread_mutex_destroy(&free_philo->alive_mutex);
			free(free_philo);
		}
		god->philos = god->philos->r_philo;
		pthread_mutex_destroy(&god->simulation_mutex);
		pthread_mutex_destroy(&god->print_mutex);
		++i;
	}
}

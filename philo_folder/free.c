/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:53:41 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/02 10:19:13 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_philos(t_god *god)
{
	int	i;
	t_philo	*free_philo;

	i = 0;
	while (i < god->philo_num)
	{
		free_philo = god->philos;
		god->philos = god->philos->r_philo;
		pthread_mutex_destroy(free_philo->r_fork);
		free(free_philo);
		++i;
	}
}
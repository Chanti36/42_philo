/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:56:31 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/02 10:18:30 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *end_philos(void *god)
{
	int	i;

	i = 0;
	while (i < ((t_god *)god)->philo_num)
	{
		printf("_____closed philo %d_____\n", ((t_god *)god)->philos->id);
		((t_god *)god)->philos->state = DEAD_STATE;
		((t_god *)god)->philos = ((t_god *)god)->philos->r_philo;
		++i;
	}
	return (NULL);
}

void	*god_thread(void *god)
{
	t_philo	*philo;

	philo = ((t_god *)god)->philos;
	while (1)
	{
		if (philo->die_timer <= 0)
		{
			printf("%lld: 💀 - philo %d - DIED\n", get_time() - philo->start_time, \
			philo->id);
			end_philos(god);
			return (NULL);
		}
		else if (philo->loop_count >= ((t_god *)god)->loops)
		{
			printf("%lld: 🥳 - COMPLETED - 🥳\n", get_time() - philo->start_time);
			end_philos(god);
			return (NULL);
		}
		philo = philo->r_philo;
	}
	return (NULL);
}

void do_threads(t_god *god, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_create(&god->thread, NULL, &god_thread, (void *)god);
	printf("GOD Created\n");
	while (i < god->philo_num)
	{
		printf("created\n");
		if (pthread_create(&philo->thread, NULL, &philo_loop, (void *)philo) != 0)
			exit(1);
		philo = philo->r_philo;
		++i;
	}
	i = 0;
	pthread_join(god->thread, NULL);
	printf("GOD ENDED\n");
	while (i < god->philo_num)
	{
		if (philo->thread)
			pthread_join(philo->thread, NULL);
		philo = philo->r_philo;
		++i;
	}
	printf("PHILOS ENDED\n");	
}

void	leaks()
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_god			god;

	atexit(leaks);
	philo = NULL;
	if (init_vals(argc, argv, &god) == 1)
		return (printf("BAD INPUT\n"), 1);
	if (god.philo_num < 2)
		return (printf ("NOT ENOUGHT PHILOS\n"), 1);
	if (initialize(&philo, &god) == 1)
		return (1);
	do_threads(&god, philo);
	
	free_philos(&god);

	return (1);
}

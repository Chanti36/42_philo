/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:56:31 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/13 13:14:37 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks()
{
	system("leaks -q philo");
}

static void	*end_philos(void *god)
{
	int	i;

	i = 0;
	while (i < ((t_god *)god)->philo_num)
	{
		((t_god *)god)->philos->state = DEAD_STATE;
		((t_god *)god)->philos = ((t_god *)god)->philos->r_philo;
		++i;
	}
	return (NULL);
}

static void	*god_thread(void *god)
{
	t_philo	*philo;

	philo = ((t_god *)god)->philos;
	while (1)
	{
//		ft_usleep(1);
		if (philo->die_timer <= 0)
		{
			print_result(god, philo, 0);
			end_philos(god);
			return (NULL);
		}
		else if (((t_god *)god)->loops > 0 && \
		philo->loop_count >= ((t_god *)god)->loops)
		{
			print_result(god, philo, 1);
			end_philos(god);
			return (NULL);
		}
		pthread_mutex_lock(&philo->god->timer_mutex);
		philo->die_timer -= 1;
		pthread_mutex_unlock(&philo->god->timer_mutex);		
		philo = philo->r_philo;
	}
}

void	do_threads(t_god *god, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&god->alive_mutex);
	while (i < god->philo_num)
	{
		if (pthread_create(&philo->thread, NULL, &philo_loop, (void *)philo) != 0)
			exit(1);
		philo = philo->r_philo;
		++i;
	}
	pthread_create(&god->thread, NULL, &god_thread, (void *)god);
	pthread_mutex_unlock(&god->alive_mutex);
	i = 0;
	pthread_join(god->thread, NULL);
	while (i < god->philo_num)
	{
		if (philo->thread)
			pthread_join(philo->thread, NULL);
		philo = philo->r_philo;
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_god			god;

	atexit(leaks);
	philo = NULL;
	if (init_vals(argc, argv, &god) == 1)
		return (printf("BAD INPUT\n"), 1);
	if (initialize(&philo, &god) == 1)
		return (printf("INIT ERROR\n"),1);
	if (god.philo_num < 2)
		return (printf ("NOT ENOUGHT PHILOS\n"), 1);
	do_threads(&god, philo);
	free_philos(&god);
	return (1);
}

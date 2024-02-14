/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:56:31 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/14 15:51:40 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*god_thread(void *god)
{
	t_philo	*philo;
	int		result;

	philo = ((t_god *)god)->philos;
	while (1)
	{
		pthread_mutex_lock(&philo->timer_mutex);
		result = check_end((t_god *)god);
		pthread_mutex_unlock(&philo->timer_mutex);
		if (result != 0)
			return (NULL);
	}
}

void	do_threads(t_god *god, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&god->simulation_mutex);
	while (i < god->philo_num)
	{
		if (pthread_create(&philo->thread, NULL, \
		&philo_loop, (void *)philo) != 0)
			exit(1);
		philo = philo->r_philo;
		++i;
	}
	god->start_time = get_time();
	pthread_create(&god->thread, NULL, &god_thread, (void *)god);
	pthread_mutex_unlock(&god->simulation_mutex);
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

static void	do_one_philosopher(t_god *god)
{
	god->start_time = get_time();
	print_state(STATE_THINKING, god->philos);
	printf("%lld %d has taken a fork\n", \
	get_time() - god->start_time, 1);
	ft_usleep(god->die_timer);
	print_result(god, god->philos, 0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_god			god;

	philo = NULL;
	if (init_vals(argc, argv, &god) == 1)
		return (printf("BAD INPUT\n"), 1);
	if (initialize(&philo, &god) == 1)
		return (printf("INIT ERROR\n"), 1);
	if (god.philo_num < 1)
		return (printf ("NOT ENOUGHT PHILOS\n"), 1);
	else if (god.philo_num == 1)
		do_one_philosopher(&god);
	else
		do_threads(&god, philo);
	free_philos(&god);
	return (1);
}

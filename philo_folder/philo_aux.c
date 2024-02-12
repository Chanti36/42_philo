/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:30:49 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/12 12:03:33 by sgil-moy         ###   ########.fr       */
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

int	ft_usleep(long long int milliseconds)
{
	long long int	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print_state(int state, t_philo philo)
{
	if (philo.god)
		pthread_mutex_lock(philo.god->print_mutex);

	if (state == STATE_THINKING)
	{
		printf("%lld: 🤔 - philo %d - began thinking\n", \
		get_time() - philo.start_time, philo.id);
	}
	else if (state == STATE_EATING)
		printf("%lld: 😋 - philo %d - began eating\n", \
		get_time() - philo.start_time, philo.id);
	else if (state == STATE_SLEEPING)
		printf("%lld: 😴 - philo %d - began sleeping\n", \
		get_time() - philo.start_time, philo.id);
	if (philo.god)
		pthread_mutex_unlock(philo.god->print_mutex);
}

void	print_result(t_god *god, t_philo *philo, int state)
{
	pthread_mutex_lock(god->print_mutex);

	if (state == 0)
		printf("%lld: 💀 - philo %d - DIED\n", get_time() - philo->start_time, \
		philo->id);
	else if (state == 1)
		printf("%lld: 🥳 - COMPLETED - 🥳\n", get_time() - philo->start_time);

	pthread_mutex_unlock(god->print_mutex);
}
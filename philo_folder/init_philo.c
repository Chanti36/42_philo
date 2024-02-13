/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:58:46 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/13 13:04:59 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*get_last_philo(t_philo *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->r_philo != NULL)
		return (get_last_philo(lst->r_philo));
	return (lst);
}

static void	add_philo_back(t_philo **lst, int id, t_god *god)
{
	t_philo	*last;
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (new == NULL)
		return ;
	new->id = id;
	new->r_philo = NULL;
	last = get_last_philo(*lst);
	if (last == NULL)
	{
		new->god = god;	
		*lst = new;
	}
	else
	{
		new->god = god;
		last->r_philo = new;
		new->l_philo = last;
		new->l_fork = &last->r_fork;
	}
}

static long int	ft_atoi(const char *str, int *flag)
{
	long int	n;
	long int	sign;

	n = 0;
	sign = 1;
	*flag = -1;
	while (*str >= '0' && *str <= '9')
	{
		*flag = 1;
		n *= 10;
		n += *str - 48;
		++str;
	}
	if (*str != '\0')
		*flag = -1;
	n *= sign;
	return (n);
}

 int	init_vals(int argc, char **argv, t_god *god)
{
	int	flag;

	if (argc < 5 || argc > 6)
		return (1);
	god->loops = 0;
	flag = 0;
	if (argc == 6)
	{
		god->loops = ft_atoi(argv[5], &flag);
		if (flag == -1 || god->loops < 1)
			return (1);
	}
	god->philo_num = ft_atoi(argv[1], &flag);
	if (flag == -1 || god->philo_num < 1)
		return (1);
	god->die_timer = ft_atoi(argv[2], &flag);
	if (flag == -1 || god->die_timer < 1)
		return (1);
	god->eat_timer = ft_atoi(argv[3], &flag);
	if (flag == -1 || god->eat_timer < 1)
		return (1);
	god->sleep_timer = ft_atoi(argv[4], &flag);
	if (flag == -1 || god->sleep_timer < 1)
		return (1);
	return (0);
}

int	initialize(t_philo **philo, t_god *god)
{
	int		i;
	t_philo	*last_philo;

	i = 0;
	*philo = NULL;
	while (i < god->philo_num)
	{
		add_philo_back(philo, i + 1, god);
		last_philo = get_last_philo(*philo);
		last_philo->state = ALIVE_STATE;
		last_philo->loop_count = 0;
		last_philo->loops = god->loops;
		last_philo->die_timer = god->die_timer;
		last_philo->die_val = god->die_timer;
		last_philo->eat_timer = god->eat_timer;
		last_philo->sleep_timer = god->sleep_timer;
		pthread_mutex_init(&last_philo->r_fork, NULL);
		++i;
	}
	last_philo->r_philo = *philo;
	last_philo->r_philo->l_philo = last_philo;
	last_philo->r_philo->l_fork = &last_philo->r_fork;
	god->philos = *philo;
	pthread_mutex_init(&god->print_mutex, NULL);
	pthread_mutex_init(&god->alive_mutex, NULL);
	pthread_mutex_init(&god->timer_mutex, NULL);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_end_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:39:54 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/12 18:17:17 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ph_check_dead_time(t_ph_philo *philo)
{
	if (ph_gettime(philo->config) - \
			philo->last_eat >= \
			(unsigned long long)philo->config->t_die)
		return (1);
	return (0);
}

int	ph_philo_died(t_ph_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&(philo->config->dead_flag_mutex));
	is_dead = (philo->config->dead_flag == 1);
	return (pthread_mutex_unlock(&(philo->config->dead_flag_mutex)), !is_dead);
}

void	ph_check_dead_execution(t_ph_config *config, t_ph_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&(philo->config->dead_flag_mutex));
	config->dead_flag = 1;
	pthread_mutex_unlock(&(config->dead_flag_mutex));
	time = (ph_gettime(philo->config) - philo->config->start_time);
	pthread_mutex_lock(&(philo->config->print));
	printf("%llu %d %s", (unsigned long long)time, \
		philo->ph_id, config->mesgs->died);
	pthread_mutex_unlock(&(philo->config->print));
	pthread_mutex_unlock(&(philo->last_eat_mutex));
}

void	ph_check_dead(t_ph_config *config)
{
	int			i;
	int			all_philos_done;

	while (1)
	{
		all_philos_done = 1;
		i = 0;
		while (i < config->nbr_philo)
		{
			pthread_mutex_lock(&(config->philos[i]->last_eat_mutex));
			if (ph_check_dead_time(config->philos[i]))
				if (!ph_is_eating(config->philos[i]) && \
					ph_check_count_eating(config->philos[i]))
					return (ph_check_dead_execution(config, \
						config->philos[i]));
			if (ph_check_count_eating(config->philos[i]) != 0)
				all_philos_done = 0;
			pthread_mutex_unlock(&(config->philos[i]->last_eat_mutex));
			i++;
		}
		usleep(100);
		if (all_philos_done)
			break ;
	}
}

int	ph_check_count_eating(t_ph_philo *philo)
{
	int	eating_count;

	pthread_mutex_lock(&(philo->eating_count_mutex));
	eating_count = philo->eating_count;
	if (philo->config->must_eat != -1 && eating_count >= \
		philo->config->must_eat)
		return (pthread_mutex_unlock(&(philo->eating_count_mutex)), 0);
	pthread_mutex_unlock(&(philo->eating_count_mutex));
	return (1);
}

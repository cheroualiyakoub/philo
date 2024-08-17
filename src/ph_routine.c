/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:48:55 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/12 19:39:32 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ph_take_fork(t_ph_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	pthread_mutex_lock(&(philo->config->global_mutex_fork));
	if (&(philo->fork_l_mutex) <= philo->fork_r_mutex)
	{
		first_fork = &(philo->fork_l_mutex);
		second_fork = philo->fork_r_mutex;
	}
	else
	{
		first_fork = philo->fork_r_mutex;
		second_fork = &(philo->fork_l_mutex);
	}
	pthread_mutex_lock(first_fork);
	ph_lock_and_print(philo, philo->config->mesgs->taken_fork);
	if (philo->config->nbr_philo == 1)
		return (pthread_mutex_unlock(first_fork), \
			pthread_mutex_unlock(&(philo->config->global_mutex_fork)), 1);
	pthread_mutex_lock(second_fork);
	ph_lock_and_print(philo, philo->config->mesgs->taken_fork);
	pthread_mutex_unlock(&(philo->config->global_mutex_fork));
	return (1);
}

int	ph_philo_sleep(t_ph_philo *philo)
{
	ph_lock_and_print(philo, philo->config->mesgs->is_sleeping);
	ph_usleep(philo->config, philo->config->t_sleep);
	return (1);
}

int	ph_philo_think(t_ph_philo *philo)
{
	ph_lock_and_print(philo, philo->config->mesgs->is_thinking);
	return (1);
}

int	ph_philo_eat(t_ph_philo *philo)
{
	ph_lock_and_print(philo, philo->config->mesgs->is_eating);
	pthread_mutex_lock(&(philo->is_eating_mutex));
	philo->is_eating = 1;
	pthread_mutex_unlock(&(philo->is_eating_mutex));
	pthread_mutex_lock(&(philo->last_eat_mutex));
	philo->last_eat = ph_gettime(philo->config);
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	ph_usleep(philo->config, philo->config->t_eat);
	pthread_mutex_lock(&(philo->eating_count_mutex));
	philo->eating_count++;
	pthread_mutex_unlock(&(philo->eating_count_mutex));
	pthread_mutex_lock(&(philo->is_eating_mutex));
	philo->is_eating = 0;
	pthread_mutex_unlock(&(philo->fork_l_mutex));
	pthread_mutex_unlock(philo->fork_r_mutex);
	pthread_mutex_unlock(&(philo->is_eating_mutex));
	return (1);
}

void	*ph_routine(void *args)
{
	t_ph_philo	*philo;

	philo = (t_ph_philo *)args;
	pthread_mutex_lock(&(philo->last_eat_mutex));
	philo->last_eat = ph_gettime(philo->config);
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	if ((philo->ph_id % 2 == 0 || philo->ph_id == philo->config->nbr_philo) \
		&& philo->config->nbr_philo > 1)
	{
		ph_philo_think(philo);
		ph_usleep(philo->config, philo->config->t_eat / 2);
	}
	while (ph_philo_died(philo) && \
		ph_check_count_eating(philo))
	{
		ph_take_fork(philo);
		if (philo->config->nbr_philo == 1)
			return ((void *)0);
		ph_philo_eat(philo);
		ph_philo_sleep(philo);
		ph_philo_think(philo);
	}
	return ((void *)0);
}

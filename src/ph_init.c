/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 04:47:04 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/12 18:23:22 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ph_inti_mutex_philo(t_ph_philo *philo)
{
	if (pthread_mutex_init(&(philo->fork_l_mutex), NULL) != 0)
		return (ph_print_clean(philo->config, \
				philo->config->mesgs->creat_mutex));
	if (pthread_mutex_init(&(philo->is_eating_mutex), NULL) != 0)
		return (ph_print_clean(philo->config, \
				philo->config->mesgs->creat_mutex));
	if (pthread_mutex_init(&(philo->last_eat_mutex), NULL) != 0)
		return (ph_print_clean(philo->config, \
				philo->config->mesgs->creat_mutex));
	if (pthread_mutex_init(&(philo->eating_count_mutex), \
				NULL) != 0)
		return (ph_print_clean(philo->config, \
				philo->config->mesgs->creat_mutex));
	return (1);
}

int	ph_creat_philos(t_ph_config *config)
{
	int	i;

	i = -1;
	config->philos = malloc (sizeof(t_ph_philo) * config->nbr_philo);
	while (++i < config->nbr_philo)
	{
		config->philos[i] = malloc (sizeof(t_ph_philo));
		config->philos[i]->config = config;
		config->philos[i]->ph_id = i + 1;
		config->philos[i]->eating_count = 0;
		config->philos[i]->is_eating = 0;
		config->philos[i]->last_eat = ph_gettime(config);
		if (ph_inti_mutex_philo(config->philos[i]) == 0)
			return (0);
	}
	i = -1;
	while (++i < config->nbr_philo)
	{
		config->philos[i]->fork_r_mutex = &(config->philos[(i + 1) \
				% config->nbr_philo]->fork_l_mutex);
	}
	return (1);
}

int	ph_creat_threads(t_ph_config *config)
{
	int			i;

	i = -1;
	config->start_time = ph_gettime(config);
	config->threads = malloc(sizeof(pthread_t) * config->nbr_philo);
	while (++i < config->nbr_philo)
		if (pthread_create(&(config->threads[i]), NULL, &ph_routine, \
				(void *)config->philos[i]) != 0)
			return (ph_print_clean(config, config->mesgs->creat_thread));
	return (1);
}

int	ph_join_threads(t_ph_config *config)
{
	int			i;

	i = -1;
	while (++i < config->nbr_philo)
		if (pthread_join(config->threads[i], NULL) != 0)
			return (ph_print_clean(config, config->mesgs->join_thread));
	return (1);
}

int	ft_isdigit(char c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

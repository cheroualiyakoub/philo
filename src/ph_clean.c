/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:01:24 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/12 19:32:18 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_philo(t_ph_config *config)
{
	int	i;

	i = -1;
	while (++i < config->nbr_philo)
	{
		if (config->philos[i])
		{
			pthread_mutex_destroy(&(config->philos[i]->fork_l_mutex));
			pthread_mutex_destroy(&(config->philos[i]->is_eating_mutex));
			pthread_mutex_destroy(&(config->philos[i]->eating_count_mutex));
			pthread_mutex_destroy(&(config->philos[i]->last_eat_mutex));
			free(config->philos[i]);
		}
	}
	free(config->philos);
}

int	ph_clean(t_ph_config *config)
{
	if (config)
	{
		if (config->mesgs)
			free(config->mesgs);
		if (config->clean_philos)
			clean_philo(config);
		if (config->clean_mutex)
		{
			pthread_mutex_destroy(&(config->dead_flag_mutex));
			pthread_mutex_destroy(&(config->print));
		}
		if (config->threads)
			free(config->threads);
		free(config);
	}
	return (1);
}

int	ph_print_clean(t_ph_config *config, char *msg)
{
	(void)config;
	printf("%s", msg);
	ph_clean(config);
	return (0);
}

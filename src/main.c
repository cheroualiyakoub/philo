/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:29:17 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/12 19:08:24 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ph_init_mesgs(t_ph_config *config)
{
	t_ph_msgs	*msgs;

	msgs = malloc(sizeof(t_ph_msgs));
	if (!msgs)
		return (ph_print_clean(config, config->mesgs->malloc_error));
	msgs->wrong_argc = "Wrong arguments\n";
	msgs->malloc_error = "Malloc error\n";
	msgs->gettime_error = "Getting time error\n";
	msgs->creat_mutex = "Error while creating a mutex\n";
	msgs->creat_mutex = "Error while trying to lock a mutex\n";
	msgs->creat_thread = "Error while creating a thread\n";
	msgs->join_thread = "Error while joining a thread\n";
	msgs->is_eating = "is eating\n";
	msgs->is_sleeping = "is sleeping\n";
	msgs->is_thinking = "is thinking\n";
	msgs->taken_fork = "has taken a fork\n";
	msgs->died = "died\n";
	config->mesgs = msgs;
	return (1);
}

int	ph_init(int argc, char **argv, t_ph_config *config)
{
	config->dead_flag = 0;
	config->clean_mutex = 0;
	config->clean_philos = 0;
	config->threads = NULL;
	if (!ph_init_mesgs(config))
		return (ph_print_clean(config, config->mesgs->malloc_error));
	if (!ph_parsing(argc, argv, config))
		return (ph_print_clean(config, config->mesgs->wrong_argc));
	config->clean_mutex = 1;
	if (pthread_mutex_init(&(config->print), NULL) != 0)
		return (ph_print_clean(config, config->mesgs->creat_mutex));
	if (pthread_mutex_init(&(config->dead_flag_mutex), NULL) != 0)
		return (ph_print_clean(config, config->mesgs->creat_mutex));
	if (pthread_mutex_init(&(config->global_mutex_fork), NULL) != 0)
		return (ph_print_clean(config, config->mesgs->creat_mutex));
	if (!ph_creat_philos(config))
		return (0);
	config->clean_philos = 1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_ph_config	*config;

	config = malloc(sizeof(t_ph_config));
	if (!config)
	{
		printf("Malloc Error\n");
		return (1);
	}
	if (!config || !ph_init(argc, argv, config))
		return (1);
	ph_creat_threads(config);
	ph_check_dead(config);
	ph_join_threads(config);
	ph_clean(config);
	return (0);
}

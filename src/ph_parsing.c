/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 04:25:05 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/08 22:38:33 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ph_check_input(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (ft_atoi(str) <= 0)
			return (0);
	}
	return (1);
}

int	ph_parsing(int argc, char **argv, t_ph_config *config)
{
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (++i < argc)
		if (!ph_check_input(argv[i]))
			return (0);
	config->nbr_philo = ft_atoi(argv[1]);
	config->t_die = ft_atoi(argv[2]);
	config->t_eat = ft_atoi(argv[3]);
	config->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		config->must_eat = ft_atoi(argv[5]);
	else
		config->must_eat = -1;
	if (config->t_die < 60 || config->t_eat < 60
		|| config->t_sleep < 60)
		return (0);
	if (config->nbr_philo > 200)
		return (0);
	return (1);
}

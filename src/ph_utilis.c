/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:22:41 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/12 17:01:39 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ph_usleep(t_ph_config *config, u_int64_t time)
{
	u_int64_t	start;

	start = ph_gettime(config);
	usleep(0.2 * time);
	while ((ph_gettime(config) - start) < time)
		usleep(100);
	return (0);
}

int	ph_lock_and_print(t_ph_philo *philo, char *msg)
{
	uint64_t	time;

	if (!ph_philo_died(philo))
		return (1);
	if (!ph_check_count_eating(philo))
		return (1);
	time = (ph_gettime(philo->config) - philo->config->start_time);
	pthread_mutex_lock(&(philo->config->print));
	printf("%llu %d %s", (unsigned long long) time, \
		philo->ph_id, msg);
	pthread_mutex_unlock(&(philo->config->print));
	return (1);
}

int	ph_is_eating(t_ph_philo *philo)
{
	int	is_eating;

	pthread_mutex_lock(&(philo->is_eating_mutex));
	is_eating = philo->is_eating;
	return (pthread_mutex_unlock(&(philo->is_eating_mutex)), is_eating);
}

u_int64_t	ph_gettime(t_ph_config *config)
{
	struct timeval	c_time;

	if (gettimeofday(&c_time, NULL))
		return (ph_print_clean(config, config->mesgs->gettime_error));
	return ((c_time.tv_sec * (u_int64_t)1000) + (c_time.tv_usec / 1000));
}

long	ft_atoi(const char *str)
{
	int		is_negative;
	int		i;
	long	result;

	i = 0;
	is_negative = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		is_negative = -1;
	if (is_negative == -1 || str[i] == '+')
		i++;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	return (result * is_negative);
}

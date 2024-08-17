/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:31:04 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/12 19:07:53 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_ph_msgs
{
	char			*malloc_error;
	char			*wrong_argc;
	char			*gettime_error;
	char			*creat_mutex;
	char			*err_lock_mutex;
	char			*err_unlock_mutex;
	char			*creat_thread;
	char			*join_thread;
	char			*is_eating;
	char			*is_thinking;
	char			*is_sleeping;
	char			*died;
	char			*taken_fork;

}	t_ph_msgs;

struct	s_ph_config;

typedef struct s_ph_philo
{
	int					ph_id;
	int					eating_count;
	uint64_t			last_eat;
	int					is_eating;
	pthread_mutex_t		eating_count_mutex;
	pthread_mutex_t		*fork_r_mutex;
	pthread_mutex_t		fork_l_mutex;
	pthread_mutex_t		is_eating_mutex;
	pthread_mutex_t		last_eat_mutex;
	struct s_ph_config	*config;
}	t_ph_philo;

typedef struct s_ph_config
{
	t_ph_msgs			*mesgs;
	pthread_t			*threads;
	int					nbr_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					must_eat;
	u_int64_t			start_time;
	u_int64_t			print_time;
	t_ph_philo			**philos;
	pthread_mutex_t		dead_flag_mutex;
	pthread_mutex_t		global_mutex_fork;
	pthread_mutex_t		print;
	int					dead_flag;
	int					clean_mutex;
	int					clean_philos;
}	t_ph_config;

int					ph_parsing(int argc, char **argv, t_ph_config *config);
int					ph_init(int argc, char **argv, t_ph_config *config);
int					ph_clean(t_ph_config *config);
int					ph_print_clean(t_ph_config *config, char *msg);
long				ft_atoi(const char *str);
int					ft_isdigit(char c);
u_int64_t			ph_gettime(t_ph_config *config);
void				*ph_routine(void *args);
int					ph_creat_philos(t_ph_config *config);
int					ph_creat_threads(t_ph_config *config);
int					ph_join_threads(t_ph_config *config);
int					ph_init_mesgs(t_ph_config *config);
int					ph_lock_and_print(t_ph_philo *philo, char *msg);
int					ph_usleep(t_ph_config *config, u_int64_t time);
void				ph_check_dead(t_ph_config *config);
int					ph_check_count_eating(t_ph_philo	*philo);
int					ph_philo_died(t_ph_philo *philo);
void				ph_check_dead_execution(t_ph_config *config, \
						t_ph_philo *philo);
void				ph_check_dead(t_ph_config *config);
int					ph_is_eating(t_ph_philo *philo);

#endif

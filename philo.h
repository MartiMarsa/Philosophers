/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:30:31 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/09/30 16:30:33 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# define PHILO_MAX 201

// Define color codes for different actions
# define COLOR_RESET "\033[0m"
# define COLOR_EAT "\033[1;32m"      // Green
# define COLOR_THINK "\033[1;34m"    // Blue
# define COLOR_SLEEP "\033[1;33m"    // Yellow
# define COLOR_DIE "\033[1;31m"      // Red

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	bool			*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	bool			dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_data;

typedef struct s_mtx
{
	pthread_mutex_t	mtx;
}				t_mtx;

// MAIN //
int main(int argc, char **argv);

// INIT //
void	parsr_args(t_philo *philo, char **argv);
void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks,
				char **argv);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_data(t_data *data, t_philo *philo);

//  UTILS //
int	ft_atoi(const char *s);
void	print_message(char *str, t_philo *philo, int id);

// CHECKER UTILS //
int	philosopher_dead(t_philo *philo, size_t time_to_die);
int	check_if_dead(t_philo *philos);
int	check_if_all_ate(t_philo *philos);

// ROUTINE STATES //
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	dream(t_philo *philo);

// TABLE //
void	destroy_all(char *str, t_data *data, t_mtx *forks);
int dead_loop(t_philo *philo);
void	*start_routine(void *ptr);
void	*POS(void *ptr);
int	thread_create(t_data *data, t_mtx *forks);

#endif
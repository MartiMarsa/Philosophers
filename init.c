/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:36:00 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/10/07 15:36:03 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Parses the users input
void	parse_args(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

// Initializes the philisophers
void	init_philos(t_philo *philos, t_data *data, t_mtx *forks, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = false;
		philos[i].meals_eaten = 0;
		parse_args(&philos[i], argv);
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].dead = &data->dead_flag;
		philos[i].write_lock = &data->write_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
	}
}

// Initializes the forks mutexes
void	init_forks(t_mtx *forks, int philo_num)
{
	int	i;

	i = -1;
	while (++i < philo_num)
		pthread_mutex_init(&forks[i], NULL);
}

// Initializing the program structure. By using this mutexes the threads 
// are not allowed to write, die or increade the numbers of meals done at the
// same time, avoiding race conditions
void	init_data(t_data *data, t_philo *philo)
{
	data->dead_flag = false;
	data->philos = &philo;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:21:28 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/09/30 18:21:30 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Destroys all the mutexes
void	destroy_all(char *str, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (++i < data->philos[0].num_of_philos)
		pthread_mutex_destroy(&forks[i]);
}

// Check if someone has died
int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

//Philo's routine
void	*start_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (ptr);
}

// Monitor thread routine
void	*pos(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (42)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (ptr);
}

// Create and protect all the threads
int	thread_create(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	waiter;
	int			i;

	if (pthread_create(&waiter, NULL, &pos, data->philos) != 0)
		destroy_all("Thread creation error", data, forks);
	i = -1;
	while (++i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&start_routine, &data->philos[i]) != 0)
			destroy_all("Thread creation error", data, forks);
	}
	if (pthread_join(waiter, NULL) != 0)
		destroy_all("Thread join error", data, forks);
	i = -1;
	while (++i < data->philos[0].num_of_philos)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_all("Thread join error", data, forks);
	return (0);
}

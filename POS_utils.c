/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   POS_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:21:28 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/09/30 18:21:30 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Print message function
void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;
	const char *color;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!ft_strcmp(str, "is eating"))
		color = COLOR_EAT;
	else if (!ft_strcmp(str, "is thinking"))
		color = COLOR_THINK;
	else if (!ft_strcmp(str, "is sleeping"))
		color = COLOR_SLEEP;
	else if (!ft_strcmp(str, "has died"))
		color = COLOR_DIE;
	else
		color = COLOR_RESET;
	if (!dead_loop(philo))
		printf("%s%zu %d %s%s\n", color, time, id, str, COLOR_RESET);
	pthread_mutex_unlock(philo->write_lock);
}

// Check if the philosopher is dead
int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
			&& !philo->eating)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

// Check if someone is dead
int	check_if_dead(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].num_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_message("died", &philos[i].dead_lock);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = true;
			phtread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
	}
	return (0);
}

//Function to determine if all the philos ate the num_of_meals
int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	done;

	if (philos[0].num_times_to_eat == -1)
		return (0);
	i = -1;
	done = 0;
	while (++i < philos[0].num_of_philos)
	{
			pthread_mutex_lock(philos[i].meal_lock);
			if (philos[i].meals_eaten == philos[i].num_times_to_eat)
				done++;
			pthread_mutex_unlock(philos[i].meal_lock);
	}
	if (done == philos[0].num_times_to_eat)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	
}

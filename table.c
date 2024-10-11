
#include "philo.h"


// Check if someone has died

int dead_loop(t_philo *philo)
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

// Create and protect all the threads
int	thread_create(t_data *data, t_mtx *forks)
{
	pthread_t	waiter;
	int			i;

	if (pthread_create(&waiter, NULL, &POS, data->philos) != 0)
		destroy_all("Thread creation error", data, forks);
	i = -1;
	while (++i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &start_routine, &data->philos[i] != 0))
			destroy_all("Thread creation error", data, forks);
	}
	if (pthread_join(waiter, NULL) != 0)
		destroy_all("Thread join error", data, forks);
	i = -1;
	while (++i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL != 0))
			destroy_all("Thread join error", data, forks);
	}
	return (0);
}

#include "philo.h"

// Think function
void    think(t_philo *philo)
{
    print_message("was caught on a mental loop", philo, philo->id);
}

// Dream function
void    dream(t_philo *philo)
{
    print_message("is sleeping like a log", philo, philo->id);
    ft_usleep(philo->time_to_sleep);
}


// Eat function
void    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print_message("has taken the right fork", philo, philo->id);
    if (philo->num_of_philos == 1)
    {
        ft_usleep(philo->time_to_die);
        pthread_mutex_unlock(philo->r_fork);
        return;
    }
    pthread_mutex_lock(philo->l_fork);
    print_message("has taken the left fork", philo, philo->id);
    philo->eating = true;
    print_message("is eating like a horse", philo, philo->id);
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_to_eat);
    philo->eating = false;
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}
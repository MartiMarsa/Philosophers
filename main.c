/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:31:03 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/09/30 16:31:05 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **argv);
static void	args_legend(void);

int	main(int argc, char **argv)
{
	t_data				data;
	t_philo				philo[PHILO_MAX];
	pthread_mutex_t		forks[PHILO_MAX];

	if ((argc != 5 && argc != 6) || check_args(argv))
		return (args_legend(), 1);
	init_data(&data, philo);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philo, &data, forks, argv);
	thread_create(&data, forks);
	destroy_all(NULL, &data, forks);
	return (0);
}

static int	check_arg_content(char *argv)
{
	while (*argv)
	{
		if (*argv < '0' || *argv > '9')
			return (1);
		argv++;
	}
	return (0);
}

static void	args_legend(void)
{
	write(2, "\nList of valid arguments\n", 25);
	write(2, "Philophers from 0 to 200\n", 25);
	write(2, "Time to die from 60 to 1000000 (ms)\n", 36);
	write(2, "Time to eat from 60 to 1000000 (ms)\n", 36);
	write(2, "Time to sleep from 60 to 1000000 (ms)\n", 38);
	write(2, "Times to eat from 0 1000000 (OPTIONAL)\n\n", 40);
}

static int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200
		|| check_arg_content(argv[1]) == 1)
		return (write(2, "Invalid number of philophers\n", 29));
	if (ft_atoi(argv[2]) <= 0 || ft_atoi (argv[2]) < 60
		|| ft_atoi(argv[2]) > 1000000 || check_arg_content(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 20));
	if (ft_atoi(argv[3]) <= 0 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[3]) > 1000000 || check_arg_content(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 20));
	if (ft_atoi(argv[4]) <= 0 || ft_atoi(argv[4]) < 60
		|| ft_atoi(argv[4]) > 1000000 || check_arg_content(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 22));
	if ((argv[5] && ft_atoi(argv[5]) <= 0)
		|| (argv[5] && ft_atoi(argv[5]) > 1000000)
		|| (argv[5] && check_arg_content(argv[5]) == 1))
		return (write(2, "Invalid must eat times\n", 23));
	return (0);
}

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

/*  los argumentos deben ser numericos. maximo numero de filosofos 200. minimo de tiempo 60 ms  */

int	check_args(char **argv);

int	main(int argc, char **argv)
{
	if (argc != 5 || argc != 6)
		return (write(1, "Invalid number of arguments\n", 28));
	if (check_args(argv) != 0)
		return (0);
		
}

int	check_arg_content(char *argv)
{
	while (*argv)
	{
		if (*argv < '0' || *argv > '9')
			return (1);
		argv++;
	}
	return (0);
}

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200 || check_arg_content(argv[1]) == 1)
		return (write(1, "Invalid number of philophers\n"));
	if (ft_atoi(argv[2]) <= 0 || ft_atoi (argv[2]) < 60 || check_arg_content(argv[2]) == 1)
		return (write(1, "Invalid time to die\n", 20));
	if (ft_atoi(argv[3]) <= 0 || ft_atoi (argv[3]) < 60 || check_arg_content(argv[3]) == 1)
		return (write(1, "Invalid time to eat\n", 20));
	if (ft_atoi(argv[4]) <= 0 || ft_atoi (argv[4]) < 60 || check_arg_content(argv[4]) == 1)
		return (write(1, "Invalid time to sleep\n", 22));
	if (argv[6] && ft_atoi(argv[6]) <= 0 || argv[6] && check_arg_content(argv[5]) == 1)
		return (write(1, "Invalid number of times each philosopher must eat\n", 50));
	return (0);
}
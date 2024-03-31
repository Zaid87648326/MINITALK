/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:57:01 by msabri            #+#    #+#             */
/*   Updated: 2024/03/31 00:20:58 by msabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *s)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (s[i] == ' ' || (s[i] >= 7 && s[i] <= 13))
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10;
		num = num + s[i] - 48;
		i++;
	}
	return (num * sign);
}

void	new_line(int pid)
{
	int	j;
	int	bit;

	j = 7;
	bit = 0;
	while (j >= 0)
	{
		bit = '\n' >> j;
		if (bit & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		j--;
		usleep(250);
	}
}

void	send(char *msg, int pid)
{
	int	i;
	int	j;
	int	bit;

	i = 0;
	while (msg[i] != '\0')
	{
		j = 7;
		bit = 0;
		while (j >= 0)
		{
			bit = msg[i] >> j;
			if (bit & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j--;
			usleep(250);
		}
		i++;
	}
	new_line(pid);
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	i = 0;
	if (ac != 3)
	{
		write(1, "usage: ./client [pid] [msg]\n", 28);
		return (0);
	}
	while (av[1][i])
	{
		if (av[1][i] < '0' || av[1][i] > '9')
		{
			write(1, "BAD PID\n", 8);
			return (0);
		}
		i++;
	}
	pid = ft_atoi(av[1]);
	send(av[2], pid);
	return (0);
}

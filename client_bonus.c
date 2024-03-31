/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:56:32 by msabri            #+#    #+#             */
/*   Updated: 2024/03/31 00:20:53 by msabri           ###   ########.fr       */
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

void	newline(int pid)
{
	int	c;
	int	tmp;
	int	j;

	c = '\n';
	j = 7;
	while (j >= 0)
	{
		tmp = c >> j;
		if (tmp & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		j--;
		usleep(250);
	}
}

void	send(char *msg, int pid)
{
	int	bit;
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 7;
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
	newline(pid);
}

void	handler(int s)
{
	if (s == SIGUSR1)
		write(1, "message wssel\n", 15);
	exit(1);
}

int	main(int ac, char **v)
{
	int pid;
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	if (ac != 3)
	{
		write(1, "bad using \n USAGE : ./client [PID] [MSG]\n", 42);
	}
	int i = 0;
	while (v[1][i])
	{
		if (!(v[1][i] >= '0' && v[1][i] <= '9'))
		{
			write(1, "bad pid\n", 8);
			return (0);
		}
		i++;
	}
	pid = ft_atoi(v[1]);
	send(v[2], pid);
	while (1)
	{
		pause();
	}
	return (0);
}
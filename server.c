/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:56:37 by msabri            #+#    #+#             */
/*   Updated: 2024/03/31 00:21:03 by msabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	putnbr(int n)
{
	char	c;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	else if (n < 10)
	{
		c = n + 48;
		write(1, &c, 1);
	}
	else
	{
		c = (n % 10) + 48;
		putnbr(n / 10);
		write(1, &c, 1);
	}
}

void	sighandler(int s)
{
	static int	i;
	static int	gtr;

	i = 0;
	gtr = 0;
	if (s == SIGUSR1)
	{
		gtr = gtr << 1;
		gtr = gtr | 1;
	}
	else
	{
		gtr = gtr << 1;
	}
	if (i == 7)
	{
		write(1, &gtr, 1);
		gtr = 0;
		i = 0;
		return ;
	}
	i++;
}

int	main(void)
{
	int p = getpid();
	write(1, "WELCOME TO MINITALK\nPID :", 26);
	putnbr(p);
	write(1, "\n", 1);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);
	while (1)
	{
		pause();
	}
	return (0);
}
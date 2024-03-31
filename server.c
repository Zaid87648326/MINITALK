/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabri <msabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:56:37 by msabri            #+#    #+#             */
/*   Updated: 2024/03/31 13:48:28 by msabri           ###   ########.fr       */
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
	static char	char_bit;
	static int	i;

	char_bit = char_bit << 1;
	if (s == SIGUSR1)
		char_bit = char_bit | 1;
	i++;
	if (char_bit && i > 7)
	{
		write(1, &char_bit, 1);
		char_bit = 0;
		i = 0;
	}
	else if (!char_bit && i > 7)
	{
		char_bit = 0;
		i = 0;
	}
}

int	main(void)
{
	int	p;

	p = getpid();
	write(1, "WELCOME TO MINITALK\nPID : ", 26);
	putnbr(p);
	write(1, "\n", 1);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);
	while (1)
	{
	}
	return (0);
}

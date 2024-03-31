/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabri <msabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:56:29 by msabri            #+#    #+#             */
/*   Updated: 2024/03/31 12:39:50 by msabri           ###   ########.fr       */
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

void	reponse(pid_t pid)
{
	kill(pid, SIGUSR1);
}

void	handler(int s, siginfo_t *siginfo, void *context)
{
	static int	i = 0;
	static int	ctr = 0;

	(void)context;
	if (s == SIGUSR1)
	{
		ctr = ctr << 1;
		ctr = ctr | 1;
	}
	else
	{
		ctr = ctr << 1;
	}
	if (i == 7)
	{
		write(1, &ctr, 1);
		if (ctr == '\n')
			reponse(siginfo->si_pid);
		ctr = 0;
		i = 0;
		return ;
	}
	i++;
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	write(1, "HI ,Welcome to MINITALK\n", 24);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "the PID is :", 12);
	putnbr(pid);
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}

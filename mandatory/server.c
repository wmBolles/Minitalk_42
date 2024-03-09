/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 06:05:26 by wabolles          #+#    #+#             */
/*   Updated: 2024/03/09 21:55:41 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	hundler(int sig)
{
	if (sig == SIGUSR1) write(1, "1", 1);
 	else if (sig == SIGUSR2) write(1, "0", 1);
	write(1, " ", 1);
}

void	ft_putchar(char c){ write(1, &c, 1); }

void	ft_putnbr(int n)
{
	if (n >= 0)
	{
		if (n > 9)
			ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
	}
}

int		main(void)
{
	write(1, "pid: ", 5);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	for (;;)
	{
		signal(SIGUSR1, hundler);
		signal(SIGUSR2, hundler);
		pause();
	}	
}

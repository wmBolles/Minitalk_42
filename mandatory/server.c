/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 06:05:26 by wabolles          #+#    #+#             */
/*   Updated: 2024/03/10 20:15:22 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handle_signal(int sig, siginfo_t *info,
void __attribute__ ((unused)) *unused)
{
	static char		byte;
	static pid_t	pid;
	static int		bit = 0;

	if (info->si_pid != pid)
	{
		byte = 0;
		bit = 0;
		pid = info->si_pid;
	}
	bit++;
	if (sig == SIGUSR1)
		byte++;
	if (bit <= 7)
		byte <<= 1;
	else
	{
		write(1, &byte, 1);
		byte = 0;
		bit = 0;
	}
}

int	main(void)
{
	struct sigaction	signal;

	signal.sa_sigaction = &handle_signal;
	signal.sa_flags = SA_SIGINFO;
	print_intro(getpid());
	while (1)
	{
		if (sigaction(SIGUSR1, &signal, NULL) == -1)
		{
			ft_printf("Sigaction Sigusr1 Error!\n");
			return (1);
		}
		if (sigaction(SIGUSR2, &signal, NULL) == -1)
		{
			ft_printf("Sigaction Sigusr2 Error!\n");
			return (1);
		}
		pause();
	}
}

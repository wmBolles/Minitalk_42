/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 08:16:41 by wabolles          #+#    #+#             */
/*   Updated: 2024/03/11 16:56:37 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handler(int __attribute__ ((unused)) sig)
{
	ft_printf("The message completely received !\n");
}

int	check_process_id(char *pid)
{
	int		index;

	if (!pid)
		return (1);
	index = 0;
	while (pid[index] == 32)
		index++;
	while (pid[index])
	{
		if (!(pid[index] >= '0' && pid[index] <= '9'))
			return (1);
		index++;
	}
	return (0);
}

int	send_bits(int pid, char byte)
{
	int		index;

	index = 7;
	while (index >= 0)
	{
		if (((byte >> index) & 1) == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("Error in Sending of SIGUSR1 !\n");
				return (1);
			}
		}
		else if (((byte >> index) & 1) == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("Error in Sending of SIGUSR2 !\n");
				return (1);
			}
		}
		usleep(400);
		index--;
	}
	return (0);
}

void	send_bytes(int pid, char *msg)
{
	int		index;

	if (!msg)
		return ;
	if (pid <= 0)
		return ;
	index = 0;
	while (msg[index])
	{
		if (send_bits(pid, msg[index]))
			return ;
		index++;
	}
	send_bits(pid, '\0');
}

int	main(int ac, char *av[1])
{
	signal(SIGUSR2, handler);
	if (ac == 3)
	{
		if (check_process_id(av[1]))
		{
			ft_printf("Bad process id !\n");
			return (1);
		}
		else
		{
			send_bytes(ft_atoi(av[1]), av[2]);
			return (0);
		}
	}
	else
	{
		ft_printf("Please Enter the pid followed by message !\n");
		return (1);
	}
}

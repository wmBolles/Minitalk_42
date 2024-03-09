/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 06:45:14 by wabolles          #+#    #+#             */
/*   Updated: 2024/03/09 22:01:59 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	ft_atoi(char *str)
{
	int		res;

	res = 0;
	while (*str)
	{
		res *= 10;
		res += *str - 48;
		str++;
	}
	return (res);
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

void	send_bits(int pid, char byte)
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
				return ;
			}
		}
		else if (((byte >> index) & 1) == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("Error in Sending of SIGUSR2 !\n");
				return ;
			}
		}
		usleep(300);
		index--;
	}
}

void	send_bytes(int pid, char *msg)
{ 
	int		index;

	if (!msg)
		return ;
	index = 0;
	while (msg[index])
	{
		send_bits(pid, msg[index]);
		index++;
	}
	send_bits(pid, '\0');
}

int		main(int ac, char *av[1])
{
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
		ft_printf("Please Enter the pid followed by message");
}
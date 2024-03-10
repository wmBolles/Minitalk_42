/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_at_destructor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:36:12 by wabolles          #+#    #+#             */
/*   Updated: 2024/03/10 20:59:17 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_two_returns	add_addresses(char *addr)
{
	static short		index;
	static char			*addresses[10];
	t_two_returns		node;

	addresses[index] = addr;
	node.allocations_number = index;
	node.allocations = addresses;
	index++;
	return (node);
}

void	_end_func(void)
{
	char			**addresses;
	int				index;
	short			n_allocs;
	t_two_returns	the_final_node;	

	index = 0;
	the_final_node = add_addresses(NULL);
	n_allocs = the_final_node.allocations_number;
	addresses = the_final_node.allocations;
	while (index < n_allocs)
	{
		free(addresses[index]);
		index++;
	}
}

void	print_intro(int pid)
{
	ft_printf("\n\033[1;33m");
	ft_printf("███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗ \n");
	ft_printf("██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗\n");
	ft_printf("███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝\n");
	ft_printf("╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗\n");
	ft_printf("███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║\n");
	ft_printf("╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝\n");
	ft_printf("Process ID: \033[1;34m%d\033[1;30m\t", pid);
	ft_printf("     Created By: wabolles\n\n>> \033[1;0m");
}

int	ft_atoi(const char *str)
{
	int		res;

	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - 48;
		str++;
	}
	return (res);
}

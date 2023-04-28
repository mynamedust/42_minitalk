/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:15:58 by almeliky          #+#    #+#             */
/*   Updated: 2023/04/22 22:41:00 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_errprint(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
	exit(1);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long int	result;

	sign = 1;
	result = 0;
	if (!*str)
		return (0);
	while (*str == 9 || *str == 10 || *str == 11
		|| *str == 12 || *str == 13 || *str == 0 || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9') && *str)
	{
		result += *str - '0';
		result *= 10;
		str++;
	}
	result /= 10;
	return (result * sign);
}

void	send_str(char *str, int pid)
{
	unsigned char	c;
	int				i;
	int				status;

	i = 7;
	while (*str)
	{
		c = *str;
		while (i >= 0)
		{
			if (((c >> i) & 1) == 1)
				status = kill(pid, SIGUSR1);
			else
				status = kill(pid, SIGUSR2);
			if (status < 0)
				ft_errprint("Client: Singnal sending error.\n");
			i--;
			usleep(500);
		}
		i = 7;
		str++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		ft_errprint("Client: Error. Invalid number of arguments.\n");
	send_str(argv[1], ft_atoi(argv[2]));
	exit(0);
}

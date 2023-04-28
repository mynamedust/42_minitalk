/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:36:56 by almeliky          #+#    #+#             */
/*   Updated: 2023/04/26 16:56:55 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int	g_mess_len = 0;

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

void	send_str(char *str, int pid, struct sigaction *sa)
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
			if (sigaction(SIGUSR2, sa, NULL) == -1)
				ft_errprint("Client: Signal handling error.\n");
		}
		i = 7;
		g_mess_len++;
		str++;
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	(void)sig;
	g_mess_len--;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (argc != 3)
		ft_errprint("Client: Error. Invalid number of arguments.\n");
	send_str(argv[1], ft_atoi(argv[2]), &sa);
	if (g_mess_len == 0)
		write(1, "Client: The message was successfully received.\n", 61);
	exit(0);
}

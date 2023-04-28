/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:06:37 by almeliky          #+#    #+#             */
/*   Updated: 2023/04/26 16:58:26 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

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

void	ft_putnbr(int n)
{
	unsigned long	num;
	char			c;

	num = n;
	if (num >= 0)
	{
		c = '0' + (unsigned int)(num % 10);
		if (n == 0)
		{
			write(1, "0", 1);
			return ;
		}
		if (num / 10 != 0)
			ft_putnbr(num / 10);
		write(1, &c, 1);
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	g_bit;
	static int				i;

	(void)context;
	g_bit = g_bit * 2;
	if (sig == SIGUSR1)
	{
		g_bit = g_bit | 1;
	}
	i++;
	if (i == 8)
	{
		i = 0;
		write (1, &g_bit, 1);
		g_bit = 0;
		kill(info->si_pid, SIGUSR2);
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					i;

	i = 0;
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	while (1)
	{
		if (sigaction(SIGUSR1, &sa, NULL) == -1
			|| sigaction(SIGUSR2, &sa, NULL) == -1)
			ft_errprint("Server: Signal handling error.\n");
		pause();
	}
	return (0);
}

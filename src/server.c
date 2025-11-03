/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 03:16:45 by fgorlich          #+#    #+#             */
/*   Updated: 2025/11/03 17:08:11 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static volatile sig_atomic_t	g_len = 0;

static void	ft_write_u(int fd, const unsigned char *str, size_t len)
{
	if (!str)
		return ;
	if (write(fd, str, len) < 0)
	{
	}
}

void	insert_bits(int signum, char	*buffer_string)
{
	static int				bit_index = 0;
	static char	c = 0;

	if (signum == SIGINT)
		exit(0);
	if (signum == SIGUSR1)
		c |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		buffer_string[g_len++] = c;
		bit_index = 0;
		c = 0;
	}
}

void	server_handler(int signum, siginfo_t *info, void *context)
{
	static char		*buf;
	static int		str_len;

	(void)context;
	if (!buf)
	{
		if (signum == SIGUSR1)
			++str_len;
		else if (signum == SIGUSR2)
		{	
			buf = malloc(str_len + 1);
			if (!buf)
				exit(1);
			buf[str_len] = 0;
		}
	}
	else if (buf && g_len >= str_len)
	{
		ft_write_u(1, (const unsigned char *)buf, str_len);
		(free(buf), buf = NULL, g_len = 0, str_len = 0, pause());
	}
	else if (buf)
		insert_bits(signum, buf);
	usleep(10);
	kill(info->si_pid, SIGUSR2);
}

void	for_sigaction(struct sigaction *sa)
{
	int	error_flag;

	error_flag = 0;
	sa->sa_flags = SA_SIGINFO;
	sa->sa_handler = NULL;
	sa->sa_sigaction = server_handler;
	sigemptyset(&sa->sa_mask);
	if (sigaction(SIGUSR1, sa, NULL) == -1 && ++error_flag)
		ft_write_u(2, (unsigned char *)"SERVER: SIGUSR1", 15);
	if (sigaction(SIGUSR2, sa, NULL) == -1 && ++error_flag)
		ft_write_u(2, (unsigned char *)"SERVER: SIGUSR2", 15);
	if (sigaction(SIGINT, sa, NULL) == -1 && ++error_flag)
		ft_write_u(2, (unsigned char *)"SERVER: SIGINT", 14);
	if (error_flag)
		exit(1);
	ft_printf("Server is ready and waiting for signals...\n");
}

int	main(void)
{
	struct sigaction	sa;
	int					server_pid;

	server_pid = getpid();
	ft_printf("Server PID: %d\n", server_pid);
	for_sigaction(&sa);
	while (1)
		pause();
	return (0);
}

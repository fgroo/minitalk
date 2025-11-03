/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 03:16:48 by fgorlich          #+#    #+#             */
/*   Updated: 2025/11/03 11:37:53 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>

static volatile sig_atomic_t	g_ack_received = 1;

static void	ft_write(int fd, const char *str, size_t len)
{
	if (write(fd, str, len) < 0)
		exit(0);
}

void	send_signal_and_wait(int pid, int signum)
{
	kill(pid, signum);
	while (g_ack_received == 0)
		usleep(50);
	g_ack_received = 0;
}

static void	ack_handler(int signum)
{
	g_ack_received = 1;
	if (signum != SIGUSR2)
		exit (0);
}

int	send_char(int server_pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		while (g_ack_received == 0)
			usleep(50);
		g_ack_received = 0;
		if ((c >> i) & 1)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				return (0);
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa_client;
	int					server_pid;
	char				*message;
	size_t				i;

	if (argc != 3)
		return (ft_printf("Usage: %s <Server_PID> <Message>\n", argv[0]), 1);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	if (server_pid <= 0)
		return (ft_printf("Invalid PID.\n"), 1);
	ft_printf("Client PID: %d\n", getpid());
	sa_client.sa_handler = ack_handler;
	sigemptyset(&sa_client.sa_mask);
	if (sigaction(SIGUSR2, &sa_client, NULL) == -1)
		return (ft_write(2, "CLIENT: Error setting up SIGUSR2", 32), 1);
	i = ft_strlen(message) + 1;
	while (--i)
		send_signal_and_wait(server_pid, SIGUSR1);
	send_signal_and_wait(server_pid, SIGUSR2);
	while (message[i] && send_char(server_pid, message[i]))
		i++;
	send_char(server_pid, 0);
	return (ft_write(1, "Signal sent successfully.\n", 26), 0);
}

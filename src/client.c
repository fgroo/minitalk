/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 03:16:48 by fgorlich          #+#    #+#             */
/*   Updated: 2025/11/03 17:14:53 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>

static volatile sig_atomic_t	g_ack_received = 1;

static void	ft_write(int fd, const char *str, size_t len)
{
	if (write(fd, str, len) < 0)
		exit(0);
}

void	send_signal_and_wait(int pid, int signum)
{
	int				elapsed;

	elapsed = 0;
	if (kill(pid, signum) == -1)
		exit(0);
	g_ack_received = 0;
	while (g_ack_received == 0 && ++elapsed < 50000)
		usleep(100);
	if (elapsed >= 50000)
		exit(1);
}

static void	ack_handler(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

int	send_char(int server_pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if ((c >> i) & 1)
			send_signal_and_wait(server_pid, SIGUSR1);
		else
			send_signal_and_wait(server_pid, SIGUSR2);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa_client;
	int					server_pid;
	char				*message;
	int					i;

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
	i = ft_strlen(message);
	while (i--)
		send_signal_and_wait(server_pid, SIGUSR1);
	send_signal_and_wait(server_pid, SIGUSR2);
	while (*message)
		send_char(server_pid, *message++);
	kill(server_pid, SIGUSR2);
	return (ft_write(1, "Signal sent successfully.\n", 26), 0);
}

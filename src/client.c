#include "minitalk.h"

static volatile int	g_ack_received = 0;

static void	ft_write_void(int fd, const char *str, size_t len)
{
	if (write(fd, str, len) < 0)
		exit(0);
}

static void	ack_and_timeout_handler(int signum)
{
	if (signum == SIGUSR2)
		g_ack_received = 1;
	ft_write_void(1, "Client: OK!\n", 12);
}

int	send_char(int server_pid, char c)
{
	int	i;
	int	retries;

	i = -1;
	while (++i < 8)
	{
		retries = 0;
		while (retries <= 2)
		{
			g_ack_received = 0;
			if ((c >> i) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			alarm(1);
			pause();
			alarm(0);
			if (g_ack_received)
				break ;
			retries++;
		}
		if (retries > 2)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa_client;
	int					server_pid;
	char				*message;
	int					i;

	i = 0;
	if (argc != 3)
		return (ft_printf("Usage: %s <Server_PID> <Message>\n", argv[0]), 1);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	if (server_pid <= 0)
		return (ft_printf("Invalid PID.\n"), 1);
	ft_printf("Sending a signal to Server PID: %d\n", server_pid);
	ft_printf("Client PID: %d\n", getpid());
	sa_client.sa_handler = ack_and_timeout_handler;
	sigemptyset(&sa_client.sa_mask);
	if (sigaction(SIGUSR2, &sa_client, NULL) == -1)
		return (ft_write_void(2, "CLIENT: Error setting up SIGUSR2", 32), 1);
	if (sigaction(SIGALRM, &sa_client, NULL) == -1)
		return (ft_write_void(2, "CLIENT: Error setting up SIGALRM", 32), 1);
	while (message[i] && send_char(server_pid, message[i]))
		i++;
	send_char(server_pid, 0);
	return (ft_write_void(1, "Signal sent successfully.\n", 26), 0);
}

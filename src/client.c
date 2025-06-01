#include "minitalk.h"

static void	ft_write(int fd, const char *str, size_t len)
{
	if (write(fd, str, len) < 0)
		exit(0);
}

static void	ack_handler(int signum)
{
	if (signum != SIGUSR2)
		exit (0);
	ft_write(1, "Client: OK!\n", 12);
}

int	send_char(int server_pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
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
		pause();
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
	sa_client.sa_handler = ack_handler;
	sigemptyset(&sa_client.sa_mask);
	if (sigaction(SIGUSR2, &sa_client, NULL) == -1)
		return (ft_write(2, "CLIENT: Error setting up SIGUSR2", 32), 1);
	while (message[i] && send_char(server_pid, message[i]))
		i++;
	send_char(server_pid, 0);
	return (ft_write(1, "Signal sent successfully.\n", 26), 0);
}

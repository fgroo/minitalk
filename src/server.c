#include "minitalk.h"

static void	ft_write_void(int fd, const unsigned char *str, size_t len)
{
	if (write(fd, str, len) < 0)
	{
	}
}

void	server_handler(int signum, siginfo_t *info, void *context)
{
	static int				bit_index = 0;
	static unsigned char	c = 0;

	(void)context;
	if (signum == SIGINT)
		exit(0);
	if (signum == SIGUSR1)
		c |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (c == 0)
		{
			ft_write_void(1, (unsigned char *)"\nString Complete. PID: ", 23);
			ft_printf("%d\n", info->si_pid);
		}
		else
			ft_write_void(1, &c, 1);
		bit_index = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;
	int					server_pid;

	server_pid = getpid();
	ft_printf("Server PID: %d\n", server_pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = NULL;
	sa.sa_sigaction = server_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (ft_write_void(2, (unsigned char *)"SERVER: SIGUSR1", 15), 1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_write_void(2, (unsigned char *)"SERVER: SIGUSR2", 15), 1);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (ft_write_void(2, (unsigned char *)"SERVER: SIGINT", 14), 1);
	ft_printf("Server is ready and waiting for signals...\n");
	while (1)
		pause();
	return (0);
}

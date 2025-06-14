#include "minitalk.h"

volatile int	g_len = 0;

static void	ft_write_u(int fd, const unsigned char *str, size_t len)
{
	if (!str)
		return ;
	if (write(fd, str, len) < 0)
	{
	}
}

void	insert_bits(int signum, int *max_len, unsigned char	**buffer_string)
{
	static int				bit_index = 0;
	static unsigned char	c = 0;

	if (signum == SIGINT)
		exit(0);
	if (!*max_len && signum == SIGUSR1 && ++bit_index)
		return ;
	if (!*max_len && signum == SIGUSR2)
	{
		*max_len = bit_index / 8;
		bit_index = 0;
		*buffer_string = malloc(*max_len);
		if (!buffer_string)
			exit(1);
		return ;
	}
	if (signum == SIGUSR1)
		c |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		(*buffer_string)[g_len++] = c;
		bit_index = 0;
		c = 0;
	}
}

void	server_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	*buffer_string;
	static int				max_len = 0;

	(void)context;
	insert_bits(signum, &max_len, &buffer_string);
	kill(info->si_pid, SIGUSR2);
	if (max_len && g_len > max_len)
	{
		ft_write_u(2, (unsigned char *)"Error while transmitting", 24);
		exit(1);
	}
	if (max_len && g_len == max_len)
	{
		ft_write_u(1, buffer_string, max_len);
		ft_write_u(1, (unsigned char *)"\n", 1);
		free(buffer_string);
		g_len = 0;
		max_len = 0;
		return ;
	}
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

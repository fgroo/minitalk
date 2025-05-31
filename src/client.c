#include "minitalk.h"
int main(int ac, char  **av)
{
	t_lst	lst;
	int	pid;

	if (ac != 3)
		return (write(1, "P", 1), 0);
	pid = ft_atoi(av[1]);
	lst.message = av[2];
	lst.sa.sa_flags = SA_SIGINFO;

	 ft_printf("before sending signal");
		//sigaction(pid, lst.sa.sa_flags, &lst.sa.__sigaction_handler);
	 kill(pid, SIGUSR1);
	 return (0);
}
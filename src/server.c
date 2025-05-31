#include "minitalk.h"

int main(void)
{
	t_lst	lst;
	int	i;

	lst.sa.sa_flags = SA_SIGINFO;
	sigemptyset(&lst.sa.sa_mask);
	ft_printf("before signal\n");
	i = getpid();
	ft_printf("%i\n", i);
	pause();
	ft_printf("after signal\n");
	return (0);
}
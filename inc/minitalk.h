#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"
# include "ft_printf.h"

void	client_confirmation_handler(int signum, siginfo_t *info, void *context);
int		send_char(int server_pid, char c);
void	server_handler(int signum, siginfo_t *info, void *context);
#endif

#ifndef MINITALK_H
# define MINITALK_H


# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"

typedef struct s_lst
{
	struct sigaction sa;
	char	*message;

} t_lst;

#endif
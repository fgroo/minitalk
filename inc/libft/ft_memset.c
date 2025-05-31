/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:09:22 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/11 17:44:12 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*in;

	i = 0;
	in = s;
	while (i < n)
	{
		in[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
int	main(void)
{
	char si[10] = "Hallo";
	ft_memset(si, 'c', 3);
	printf("%s", si);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:24:13 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/11 17:51:03 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*in;
	unsigned char		*out;

	i = 0;
	in = src;
	out = dest;
	while (i < n)
	{
		out[i] = in[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char a[] = "Hallo";
	char b[] = "Tschuess";
	ft_memcpy(b, a, 3);
	printf("\n%s\n%s", a, b);
}*/

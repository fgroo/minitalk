/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:06:56 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 17:51:13 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *) s;
	while (n-- > 0)
	{
		if (*p == (unsigned char)c)
			return (p);
		p++;
	}
	return (0);
}
/*#include <stdio.h>
int main(void)
{
    char    *str = "Hallooffgl";
    printf("%s", (char *)ft_memchr(str, 'f', (sizeof(char) * 4)));
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:37:12 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 17:38:04 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char const	*in;
	unsigned char		*out;

	i = -1;
	in = (unsigned const char *)src;
	out = (unsigned char *)dest;
	if (dest < src)
		while (++i < n)
			out[i] = in[i];
	else
		while (n--)
			out[n] = in[n];
	return (dest);
}
/*int main(void)
{
    char a[] = "hallfkskfl;kdo";
    char b[] = "Tschuess";
    printf("Vor function: %s\n%s\n", a, b);
    ft_memmove(a, b, 3);  // Die ersten 3 Bytes werden auf 0 gesetzt
    printf("Nach function: %s\n%s\n", a, b);
    return (0);
}*/

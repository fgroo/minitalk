/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:08:06 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/11 16:37:59 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*in;

	i = 0;
	in = s;
	while (i < n)
		in[i++] = '\0';
}
/*int	main(void)
{
	char s[10] = "Hallo";
	ft_bzero(s + 3, 2);
	printf("%s", s);
}*/

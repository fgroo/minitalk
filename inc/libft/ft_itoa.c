/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:08:22 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 13:19:42 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int n)
{
	int	c;

	c = (n <= 0);
	while (n)
	{
		n /= 10;
		c++;
	}
	return (c);
}

unsigned int	absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	int				minus;
	char			*result;
	unsigned int	mone;
	int				k;

	k = numlen(n);
	minus = 1;
	result = 0;
	mone = absolute(n);
	result = (char *) malloc(sizeof(char) * (k + 1));
	if (!result)
		return (0);
	result[k] = 0;
	if (n < 0)
		result[0] = '-';
	if (!mone)
		result[0] = '0';
	while (mone)
	{
		result[--k] = mone % 10 + '0';
		mone /= 10;
	}
	return (result);
}
/*int	main(void)
{
	printf("%s\n", ft_itoa(1234567));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(-123));
	return (0);
}*/

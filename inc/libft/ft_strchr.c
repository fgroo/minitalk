/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:40:26 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/16 14:54:38 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	return ((char *)0);
}
/*#include <stdio.h>
int	main(void)
{
	char	*str = "Hallooffgl";
	printf("%s", ft_strchr(str, 'f'));
}*/

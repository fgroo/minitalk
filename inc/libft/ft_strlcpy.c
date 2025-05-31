/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:46:15 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 15:15:09 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
/*
int	main(void)
{
	char	a[] = "Ha;llo";
	char	b[] = "Tschuess";
	printf("%zu", ft_strlcpy(a, b,(size_t) 3));
}

int main()
{
    char dst[20];
    const char *src = "Hello, World!";

    size_t len = ft_strlcpy(dst, src, sizeof(dst));
    printf("Source string: %s\n", src);
    printf("Copied string: %s\n", dst);
    printf("Length of source string: %zu\n", len);

    return 0;
}
*/

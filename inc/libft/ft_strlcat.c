/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:52:38 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 17:12:01 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;

	destlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	if (size <= destlen)
		return (srclen + size);
	while (src[i] && (destlen + i) < (size - 1))
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (srclen + destlen);
}
/*int main()
{
    char dst[20] = "Hallo ";
    const char *src = "Welt!";
    size_t size = 3;

    // Vor dem Aufruf der Funktion
    printf("Vor strlcat: %s\n", dst);

    // Aufruf der eigenen strlcat-Funktion
    size_t result = ft_strlcat(dst, src, size);

    // Nach dem Aufruf der Funktion
    printf("Nach strlcat: %s\n", dst);
    printf("Returned value: %zu\n", result);

    return 0;

int main()
{
    char dst[20] = "Hallo ";
    const char *src = "Welt!";
    size_t size = 3;

    // Vor dem Aufruf der Funktion
    printf("Vor strlcat: %s\n", dst);

    // Aufruf der eigenen strlcat-Funktion
    size_t result = ft_strlcat(dst, src, size);
    
    // Nach dem Aufruf der Funktion
    printf("Nach strlcat: %s\n", dst);
    printf("Returned value: %zu\n", result);
    
    return 0;
}*/

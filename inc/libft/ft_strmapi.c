/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:45:12 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 13:26:06 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	char	*result;

	j = 0;
	i = 0;
	while (s[i])
	{
		i++;
	}
	result = (char *) malloc (sizeof(char) * (i + 1));
	while (j < i)
	{
		result[j] = f(j, s[j]);
		j++;
	}
	result[i] = '\0';
	return (result);
}

/*static char	rot13(unsigned int i, char c)
{
	(void) i;
	if ('a' <= c && c <= 'z')
		return ((c - 'a' + 13) % 26 + 'a');
	if ('A' <= c && c <= 'Z')
		return ((c - 'A' + 13) % 26 + 'A');
	return (c);
}
#include <stdio.h>
int main(void)
{
    char *a = "Hello, World!";  // Initialize a with a valid string
    char *transformed;

    transformed = ft_strmapi(a, rot13);  // Apply rot13 to the string

    if (transformed)  // Check if memory was allocated successfully
    {
        printf("Original: %s\n", a);
        printf("Transformed: %s\n", transformed);
        free(transformed);  // Don't forget to free the memory after use
    }

}*/
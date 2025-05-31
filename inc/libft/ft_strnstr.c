/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:46:31 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 16:26:40 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] && big[i + j] == little[j] && (i + j) < len)
			j++;
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}

/*#include <stdio.h>
int	main(void)
{
    char str[] = "Hello, world!";
    char to_find[] = "world";

    char *result = ft_strnstr("lorem ipsum dolor sit amet", "ipsumm", 30);

    if (result) 
    {
        printf("Found substring: %s\n", result);
    } 
    else 
    {
        printf("not found.\n");
    }
    return 0;
}*/

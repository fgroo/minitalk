/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:31:53 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/18 16:32:10 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*res;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (start < end && ft_strchr(set, s1[end]))
		end--;
	len = end - start + 1;
	if (len <= 0)
		return (ft_strdup(""));
	res = (char *) malloc (sizeof(char) * (len + 1));
	if (!res)
		return (0);
	ft_strlcpy(res, &s1[start], len + 1);
	res[len] = '\0';
	return (res);
}
/*#include <stdio.h>
int	main(void)
{
	char	*test = ft_strtrim("Hello, World!  ", "oleHa");
	printf("%s", test);
	free(test);
	return (0);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nix <nix@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:44:20 by nix               #+#    #+#             */
/*   Updated: 2025/05/25 17:32:28 by nix              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_mod(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!(s[i] == '0' || s[i] == '1' || s[i] == 'C'
				|| s[i] == 'E' || s[i] == 'P' || s[i] == '\n'))
			return (0);
		i++;
	}
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	i = -1;
	len = ft_strlen_mod(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (++i < len)
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*join;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	len1 = ft_strlen_mod(s1);
	len2 = ft_strlen_mod(s2);
	join = malloc(len1 + len2 + 1);
	if (!join)
		return (NULL);
	while (++i < len1)
		join[i] = s1[i];
	while (++j < len2)
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (join);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub;
	size_t	i;

	s_len = ft_strlen_mod(s);
	i = -1;
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (++i < len)
		sub[i] = s[start + i];
	sub[i] = '\0';
	return (sub);
}

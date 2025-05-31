/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nix <nix@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:26:54 by fgorlich          #+#    #+#             */
/*   Updated: 2025/05/24 22:12:17 by nix              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_skip(const char *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

char	**ft_rows(char const *s, char c)
{
	int		i;
	int		l;
	char	**etagen;

	i = 0;
	l = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c) || (s[i] != c && s[i + 1] == '\0'))
			l++;
		i++;
	}
	etagen = (char **) malloc(sizeof(char *) * (l + 1));
	if (!etagen)
		return (0);
	return (etagen);
}

char	**ft_columns(char **etagen, const char *etage, char c)
{
	char	*words;

	while (*etage)
	{
		etage = ft_skip(etage, c);
		while (*etage == c)
			etage++;
		words = (char *)etage;
		while (*etage && *etage != c)
			etage++;
		if (*etage != *words)
		{
			*etagen = (char *) malloc (etage - words + 1);
			if (!*etagen)
				return (0);
			ft_memcpy(*etagen, words, etage - words);
			(*etagen)[etage - words] = '\0';
			etagen++;
		}
	}
	*etagen = 0;
	return (etagen);
}

char	**ft_split(char const *s, char c)
{
	char	**etagen;
	int		i;
	int		k;

	i = 0;
	k = 0;
	etagen = ft_rows(s, c);
	ft_columns(etagen, s, c);
	s = ft_skip(s, c);
	while (*s)
	{
		if (*s == c)
		{
			etagen[i++][k] = '\0';
			k = 0;
			s = ft_skip(s, c);
		}
		if (*s)
			etagen[i][k++] = *s++;
	}
	return (etagen);
}

void	heymistermisterfree(char **a)
{
	int	i;

	i = 0;
	if (!a)
		return ;
	while (a[i])
		free(a[i++]);
	free(a);
}

/*#include <stdio.h>
int	main(void)
{
	int	i = 0;
	char	**a = ft_split("ggd  b  ", ' ');
	if (!a)
		return (0);
	while(a[i])
	{
  		printf("%s\n", a[i]);
		i++;
	}
	heymistermisterfree(a);
 	return (0);
}*/

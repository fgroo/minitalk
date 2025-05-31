/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:28:43 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 14:42:21 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	i;

	i = 0;
	if (size == 0 || nmemb == 0)
		return (0);
	p = malloc(nmemb * size);
	if (!p)
		return (0);
	while (i < nmemb * size)
	{
		((char *)p)[i] = 0;
		i++;
	}
	return (p);
}

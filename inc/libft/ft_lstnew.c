/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:18:13 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 19:18:05 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*zoom;

	zoom = (t_list *) malloc (sizeof(t_list) * 1);
	if (!zoom)
		return (0);
	zoom->content = content;
	zoom->next = 0;
	return (zoom);
}

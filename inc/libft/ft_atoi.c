/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:43:13 by fgorlich          #+#    #+#             */
/*   Updated: 2024/11/22 15:35:44 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_tailatoi(int minus, int result, const char *nptr)
{
	if (!(*nptr >= '0' && *nptr <= '9') || !(*nptr))
		return (result * minus);
	result = result * 10 + (*nptr - '0');
	return (ft_tailatoi(minus, result, nptr + 1));
}

int	ft_atoi(const char *nptr)
{
	int	minus;
	int	result;

	minus = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus = -1;
		nptr++;
	}
	return (ft_tailatoi(minus, result, nptr));
}
/*#include <stdio.h>
int	main(void)
{
	printf("%d", ft_atoi("      +5463466sfa4"));
}*/

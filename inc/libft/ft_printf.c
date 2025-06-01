/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nix <nix@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:43:13 by fgorlich          #+#    #+#             */
/*   Updated: 2025/06/01 14:29:19 by nix              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nbrs(unsigned long n, unsigned int base, const char *hex)
{
	char	nb;
	int		len;

	len = 0;
	if (hex && n >= 16)
	{
		len += nbrs(n / base, base, hex);
		write(1, &hex[n % base], 1);
		return (len + 1);
	}
	if (n >= base)
		len += nbrs(n / base, base, hex);
	if (hex)
		nb = hex[n % base];
	else
		nb = n % base + '0';
	write(1, &nb, 1);
	return (len + 1);
}

static int	ft_putstr(char *s, int i)
{
	if (!s && (write (1, "(null)", 6)))
		return (6);
	while (s[i])
		write (1, &s[i++], 1);
	return (i);
}

static int	ft_checks(va_list p, const char *s, unsigned long int ptr, long m)
{
	if (*s == 'd' || *s == 'i')
	{
		m = va_arg(p, int);
		if (m < 0 && (write(1, "-", 1)))
			return (nbrs(-m, 10, 0) + 1);
		return (nbrs(m, 10, 0));
	}
	if (*s == 'u')
		return (nbrs((unsigned int){(unsigned int)va_arg(p, int)}, 10, 0));
	if (*s == 'c')
		return (write(1, (char []){(char)va_arg(p, int)}, 1));
	if (*s == 's')
		return (ft_putstr(va_arg(p, char *), 0));
	if (*s == 'x')
		return (nbrs(va_arg(p, unsigned int), 16, "0123456789abcdef"));
	if (*s == 'X')
		return (nbrs(va_arg(p, unsigned int), 16, "0123456789ABCDEF"));
	if (*s == 'p')
	{
		ptr = (unsigned long int)va_arg(p, void *);
		if (!ptr)
			return (write(1, "(nil)", 5));
		return (write(1, "0x", 2) + nbrs(ptr, 16, "0123456789abcdef"));
	}
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	va_list				p;
	int					count;
	unsigned long int	ptr;
	long				ifminus;

	ifminus = 0;
	ptr = 0;
	count = 0;
	va_start(p, s);
	while (*s)
	{
		if (*s == '%' && ((s++)))
			count += ft_checks(p, s, ptr, ifminus);
		else
		{
			write(1, s, 1);
			count++;
		}
		if (*s == '%' && (write(1, "%", 1)))
			count += 2;
		s++;
	}
	va_end(p);
	return (count);
}

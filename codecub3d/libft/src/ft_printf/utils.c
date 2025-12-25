/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:04:19 by mcastrat          #+#    #+#             */
/*   Updated: 2024/11/01 16:49:44 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
		i++;
	write(1, str, i);
	return (i);
}

int	ft_0xputpointer(unsigned long long nb, int flag)
{
	int	count;

	count = 0;
	if (!nb)
		count += ft_putstr("0x0");
	if (nb)
	{
		count += ft_putstr("0x");
		count += ft_putpointer(nb, flag);
	}
	return (count);
}

int	ft_putpointer(unsigned long long nb, int flag)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (flag == 1)
		base = "0123456789ABCDEF";
	if (nb >= 16)
	{
		count += ft_putpointer(nb / 16, flag);
		count += ft_putchar(base[nb % 16]);
	}
	else
		count += ft_putchar(base[nb % 16]);
	return (count);
}

int	ft_hex(unsigned int nb, int flag)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (flag == 1)
		base = "0123456789ABCDEF";
	if (nb >= 16)
	{
		count += ft_hex(nb / 16, flag);
		count += ft_putchar(base[nb % 16]);
	}
	else
		count += ft_putchar(base[nb % 16]);
	return (count);
}

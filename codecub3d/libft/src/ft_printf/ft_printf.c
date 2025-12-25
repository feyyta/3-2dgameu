/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:03:34 by mcastrat          #+#    #+#             */
/*   Updated: 2024/11/01 16:38:43 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	check(const char str, va_list args)
{
	int	count;

	count = 0;
	if (str == 'c')
		count += ft_putchar(va_arg(args, int));
	if (str == 's')
		count += ft_putstr(va_arg(args, char *));
	if (str == 'p')
		count += ft_0xputpointer(va_arg(args, unsigned long long), 0);
	if (str == 'd' || str == 'i')
		count += ft_putnbr(va_arg(args, int));
	if (str == 'u')
		count += ft_unsignednb(va_arg(args, unsigned int));
	if (str == 'x')
		count += ft_hex(va_arg(args, unsigned int), 0);
	if (str == 'X')
		count += ft_hex(va_arg(args, unsigned int), 1);
	if (str == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (str == NULL)
		return (0);
	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += check(str[i], args);
		}
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:20:07 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 01:21:48 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;

	i = 0;
	while (src[i])
		i++;
	dlen = i;
	if (dstsize == 0)
		return (dlen);
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dlen);
}
/*
int main()
{
	char a[10] = "salut";
	char b[15] = "bonjour";
	printf(" %ld \n", ft_strlcpy(a, b, 5));
	return 0;
} */

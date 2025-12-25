/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:54:52 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 20:49:14 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	m;
	size_t	i;
	size_t	dsize;
	size_t	ssize;

	if ((dest == NULL && src == NULL) || (dest == NULL && dstsize == 0))
		return (0);
	dsize = ft_strlen(dest);
	ssize = ft_strlen(src);
	if (dstsize == 0)
		return (ssize);
	if (dstsize <= dsize)
		return (dstsize + ssize);
	m = dsize;
	i = 0;
	while ((m + i) < (dstsize - 1) && src[i])
	{
		dest[m + i] = src[i];
		i++;
	}
	dest[m + i] = '\0';
	return (dsize + ssize);
}
/*calc la taille de dest et src que on stock puis tant que 
la taille de la dest + ce que on parcour de celle ci est inferieur 
a la la taille max decider et tant que on a ps atteint la fin de l
la chaine src
int main()
{
	char a[40] = "bonjour";
	char b[40] = "salut";
	printf("%ld \n", ft_strlcat( a, b, 4));
	return 0;
}*/

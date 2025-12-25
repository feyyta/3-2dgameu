/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:08:32 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 21:20:27 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/*comparer des chaine caster en 'unisgend char' en fonction d une
 * taille donner une fois un charactere non correspondant trouver 
durant le parcour des 2 chaine grace a notre cmpt on renvoie la
difference
int main()
{
    printf("%d \n", ft_memcmp("abcf", "abcd",4));
    return 0;
}*/

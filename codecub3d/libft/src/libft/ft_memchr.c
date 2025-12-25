/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 01:48:25 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 20:46:33 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	cc;

	str = (unsigned char *)s;
	cc = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		if (str[i] == cc)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
/*cast pour renvoyer en void (pointeur generique)prcq 
 * on est dans une void l adresse memoire  a un moment ou le
 * charactere chercher est trouver dans une *s controler 
par une taille n
int main()
{
    char a[] = "lelo";
    char b = 'l';
    printf("%p \n", ft_memchr(a, b, 3));
    return 0;
}*/

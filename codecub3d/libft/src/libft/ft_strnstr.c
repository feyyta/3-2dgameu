/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:24:23 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 20:50:38 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *bigchaine, const char *sschaine, size_t n)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if ((bigchaine == NULL && sschaine == NULL)
		|| (bigchaine == NULL && n == 0))
		return (NULL);
	if (sschaine[0] == '\0')
		return ((char *) bigchaine);
	while (bigchaine[i] && i < n)
	{
		while (bigchaine[i + j] == sschaine[j] && bigchaine[i + j] && i + j < n)
		{
			j++;
			if (sschaine[j] == 0)
				return ((char *)bigchaine + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
/*recherche d une sschaine dcp pendant que on parcour la big chaine
et que on est pas a la n == iteration ou a une sous boucle qui dit
si la positio dans la big chaine + j == au meme char que la ss chaine 
et que pas finis on incermente jusqu a finir la sschaine et la return

int main()
{
    printf("%s \n", ft_strnstr("salutbg", "lu", 4));
    return 0;    
}*/

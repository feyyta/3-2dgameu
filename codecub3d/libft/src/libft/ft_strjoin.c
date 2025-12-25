/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:46:31 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 22:12:02 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	tot;
	size_t	j;
	size_t	i;
	char	*ct;

	if (!s1 || !s2)
		return (NULL);
	tot = ft_strlen(s1) + ft_strlen(s2) + 1;
	ct = malloc(sizeof(char) * tot);
	if (!ct)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ct[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ct[j + i] = s2[j];
		j++;
	}
	ct[j + i] = '\0';
	return (ct);
}
/*aloue taille pour les 2 string + \0 apres dans la s1 on met 
 * la taille des 2 qui se fera remplir de dabord s1 puis on 
 * fait pareille pour la s2 juste on change pas le compteur 
 * de l adition des 2 (j) on continue dans la lance
 * juste on rajt la s2
int main()
{
    printf("%s \n", ft_strjoin("salut", " kaka"));
    return 0;
}*/

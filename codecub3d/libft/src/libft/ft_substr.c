/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:51:05 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 22:39:29 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (i < start)
		return (ft_strdup(""));
	if (len > i - start)
		len = i - start;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*calc la 's' puis adapter la len envoyer si besoin est sinon alloc	
la mem avc la taille envoyer et '\0' puis tant que on est pas a cette
taille mettre dans l espace memoire allouer la 's' et la ou elle va
debuter en ajoutant le nbr de char jusqu a la taille fixe
int main()
{
    printf("%s \n", ft_substr("salut, bg", 3, 4));
    return 0;
}*/

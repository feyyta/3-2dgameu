/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 04:23:29 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 20:48:31 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tab;
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	tab = malloc((i + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
/*va tt simplement copier en memoire la taille d une s et 
 * copier dans un tableau le contenue de celle ci*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 04:15:49 by mcastrat          #+#    #+#             */
/*   Updated: 2025/09/01 15:13:49 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	if (count != 0 && size != 0 && (count > (2147483647 / size)))
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < (count * size))
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}
/*alloc de memoir en fonction de 2 arg on cree
 * docn un variable tmp
qui va bien garder la solution apres un ptit conteur 
qui decidera quand arrt de mettre
des zero dans l espace memoire cree et ajuster
gang*/

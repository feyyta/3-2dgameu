/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:12:10 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/26 16:41:41 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_bzero(void *s, size_t size)
{
	size_t				i;
	unsigned char		*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (size > i)
	{
		ptr[i] = 0;
		i++;
	}
}
/*on cast s pour le remple de zero en fonction d une size prcq remplir du vide
c chaud
int main()
{
	char s[10] = "lelele";
	ft_bzero(s, 5);
	printf("%s \n", s);
	return 0;
}*/

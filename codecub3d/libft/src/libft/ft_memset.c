/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:46:46 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 21:12:40 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
/*ici on envoie un char dans c qui va graille le
 * rester remplacer en focntion d une taille
regler depuis la var ptr qui caste la valeur de b
int main()
{
	char str[7] = "coucou";
	ft_memset(str,'e',4);
	printf("%s\n", str);
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 01:15:27 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 22:32:56 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0 && str[i] != (unsigned char)c)
		i--;
	if (!(str[i] == (unsigned char)c))
		return (NULL);
	return ((char *)&str[i]);
}
/*on va faire la meme que rrchr mais vers la fin
int main()
{
    char a[] = "matteo";
    printf("%s \n", ft_strchr(a, 't'));
    return 0;
}*/

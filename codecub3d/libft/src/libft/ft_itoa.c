/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:02:42 by mcastrat          #+#    #+#             */
/*   Updated: 2025/09/01 15:26:46 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	len(long nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
		i++;
	if (nbr == 0)
		i++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		l;
	int		i;
	long	nbr;
	char	*result;

	nbr = n;
	l = len(nbr);
	i = l - 1;
	result = ft_calloc(l + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		result[i] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i--;
	}
	return (result);
}
/*alors on calcule la taille du nombre donc les chiffre et pour
 * ca on le fractione par 10 tant que il devient pas 0,.. 
puis on alloc tt ca en memoire + le \0 protection tsb si negatif
l endroit 0 dans la memoire genre 
le tt debut quoi devient '-' puis on rend pos et apres on ecrit le
int en char en recuperant le premier chiffre puis /10
dans smr jusqu a ce que 0,..
int main()
{
    int nb = 2147483647;
    printf("%s \n", ft_itoa(nb));
    return 0;
}*/

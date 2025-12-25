/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:27:23 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/24 22:26:47 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	totrim(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	size_t	tot;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (totrim(set, s1[start]))
		start++;
	while (totrim(set, s1[end - 1]))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	tot = end - start;
	trim = ft_calloc(tot + 1, sizeof(char));
	if (!trim)
		return (NULL);
	i = 0;
	while (start < end)
		trim[i++] = s1[start++];
	trim[i] = '\0';
	return (trim);
}
/*on va envoyer le debut et la fin dans une fonction qui va revoyer
uen erreur donc rien a afficher si elle correspond aux char ban 
puis va calc le total de l alloc memoire qu elle doit fournir
vu que si tu soustrais tt ca tu peux facilement capter ce qu il te
reste dans ta string et on va juste partir de la fin de notre debut et
le ++ jusqu au debut de notre fin en metant tt dans trim qui est l espace
cree
int	main(void)
{
    char	s1[] = "ababbabbbaaabggbabababa";
    char	set[] = "ab";

    printf("%s\n", ft_strtrim(s1, set));
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:20:41 by mcastrat          #+#    #+#             */
/*   Updated: 2025/09/01 15:28:28 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*fill(char const *s, char *mot, int first, int last)
{
	size_t	j;

	j = 0;
	while (first < last)
	{
		mot[j] = s[first];
		j++;
		first++;
	}
	mot[j] = '\0';
	return (mot);
}

static void	safefree(char **tab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**allmot(char **tab, char const *s, char c,
		size_t motcount)
{
	size_t	i;
	size_t	n;
	int		j;
	char	*mot;

	i = 0;
	n = 0;
	while (s[i] && n < motcount)
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		mot = ft_calloc((i - j) + 1, sizeof(char));
		if (!mot)
		{
			safefree(tab, n);
			return (NULL);
		}
		tab[n] = fill(s, mot, j, i);
		n++;
	}
	tab[n] = NULL;
	return (tab);
}

static size_t	countmot(char const *s, char c)
{
	size_t	mot;
	int		i;

	mot = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			mot++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (mot);
}

char	**ft_split(char const *s, char c)
{
	int		mot;
	char	**tab;

	mot = 0;
	if (!s)
		return (NULL);
	mot = countmot(s, c);
	tab = ft_calloc(mot + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tab = allmot(tab, s, c, mot);
	return (tab);
}
/*
int	main(void)
{
	char	**tabarnak;
	int		i;
    i = 0;
	tabarnak = ft_split("hahaahah kekekeke ll       oui", ' ');
	while (tabarnak[i])
	{
		printf("%s\n", tabarnak[i]);
		i++;
	}
	return (0);
}*/

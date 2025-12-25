/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:42:49 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 21:42:17 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*m;
	void	*nm;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		nm = f(lst->content);
		m = ft_lstnew(nm);
		if (!m)
		{
			del(nm);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, m);
		lst = lst->next;
	}
	return (new);
}
/*on cree une nouvelle list en appliquant une fonction envoyer
   pui si ca foire on clear sinon on fait l operation pour 
   chaque nv mailllonnnn*/

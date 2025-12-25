/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:45:39 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 20:46:11 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*taille du nbr de maillon
int main()
{
	t_list *m1 = ft_lstnew("nm");
	t_list *m2 = ft_lstnew("kk");
	t_list *m3 = ft_lstnew("lelele");
	
	t_list *liste = m1;
	m1->next=m2;
	m2->next=m3;

	printf("%d \n", ft_lstsize(liste));
	return 0;
}*/

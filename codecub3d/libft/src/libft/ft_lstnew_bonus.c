/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:45:12 by mcastrat          #+#    #+#             */
/*   Updated: 2024/10/21 20:45:31 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*cc;

	cc = malloc(sizeof(t_list));
	if (!cc)
		return (NULL);
	cc->content = content;
	cc->next = NULL;
	return (cc);
}
/*
int main()creation de nv maillon
{
	t_list *str= ft_lstnew("Hello World");
	printf("Content = %s \n",(char *)str->content);
	free(str);
	return 0;
}*/

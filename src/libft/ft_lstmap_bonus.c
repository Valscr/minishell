/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vescaffr <vescaffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 22:03:41 by vescaffr          #+#    #+#             */
/*   Updated: 2022/05/04 17:53:59 by vescaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*dest;

	if (lst)
	{
		tmp = lst;
		dest = ft_lstnew(f(tmp->content));
		if (!dest)
			return (NULL);
		tmp = tmp->next;
		while (tmp)
		{
			new = ft_lstnew(f(tmp->content));
			if (!new)
			{
				ft_lstclear(&dest, del);
				return (NULL);
			}
			ft_lstadd_back(&dest, new);
			tmp = tmp->next;
		}
		return (dest);
	}
	return (NULL);
}

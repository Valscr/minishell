/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vescaffr <vescaffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 21:44:38 by vescaffr          #+#    #+#             */
/*   Updated: 2022/05/04 15:15:50 by vescaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ls;
	t_list	*tmp;

	ls = *lst;
	while (ls)
	{
		tmp = ls->next;
		ft_lstdelone(ls, del);
		ls = tmp;
	}
	*lst = NULL;
}

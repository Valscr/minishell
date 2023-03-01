/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 22:58:19 by marvin            #+#    #+#             */
/*   Updated: 2023/02/28 22:58:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_first(t_env *list, char *string)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->value = ft_strdup(string);
	if (!(node->value))
	{
		free(node);
		return (0);
	}
	node->next = list->next;
	list->next = node;
	return (1);
}

int	add_last(t_env *list, char *string)
{
	t_env	*node;
	t_env	*cur;

	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->value = ft_strdup(string);
	if (!(node->value))
	{
		free(node);
		return (0);
	}
	cur = list;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	node->next = NULL;
	return (1);
}

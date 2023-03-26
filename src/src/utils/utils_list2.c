/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:58:02 by valentin          #+#    #+#             */
/*   Updated: 2023/03/15 20:40:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_list(t_env *env)
{
	int		count;
	t_env	*current;

	current = env;
	count = 0;
	while (current->next != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	free_t_env_list(t_env *head)
{
	if (!head)
		return ;
	free_t_env_list(head->next);
	if (head->value)
		free_str(head->value);
	free(head);
}

int	display_env_list(t_env *head)
{
	t_env	*current;

	current = head->next;
	while (current != NULL)
	{
		ft_putstr_fd(current->value, 1);
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
	return (0);
}

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

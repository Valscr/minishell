/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:58:02 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 01:58:23 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_t_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current->next != NULL)
	{
		next = current->next;
		if (current->value)
			free_str(current->value);
		free(current);
		current = next;
	}
	free(next);
}

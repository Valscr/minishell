/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:58:02 by valentin          #+#    #+#             */
/*   Updated: 2023/03/01 00:49:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_t_env_list(t_env *head)
{
	if (!head)
		return ;
	free_t_env_list(head->next);
	if (head->value)
		free_str(head->value);
	free(head);
}

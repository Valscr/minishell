/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:48:13 by valentin          #+#    #+#             */
/*   Updated: 2023/02/28 22:31:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_unset(char *name, t_env *env)
{
	int		len;
	t_env	*cur;
	t_env	*tmp;

	len = ft_strlen(name);
	cur = env;
	while (cur->next)
	{
		if (ft_strncmp(cur->next->value, name, len) == 0)
		{
			free(cur->next->value);
			cur->next->value = NULL;
			tmp = cur->next;
			cur->next = cur->next->next;
			free(tmp);
			return (0);
		}
		cur = cur->next;
	}
	return (0);
}

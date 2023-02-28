/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:48:13 by valentin          #+#    #+#             */
/*   Updated: 2023/02/28 21:33:30 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(char *name, t_data *data)
{
	int		len;
	t_env	*cur;

	len = ft_strlen(name);
	cur = data->env;
	if (ft_strncmp(cur->value, name, len) == 0)
	{
		data->env = cur->next;
		free(cur->value);
		free(cur);
	}
	cur = data->env;
	while (cur->next)
	{
		if (ft_strncmp(cur->next->value, name, len) == 0)
		{
			free(cur->next->value);
			cur->next = cur->next->next;
		}
		cur = cur->next;
	}
	return (0);
}

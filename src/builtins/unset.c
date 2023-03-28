/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:48:13 by valentin          #+#    #+#             */
/*   Updated: 2023/03/28 05:06:56 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset_bis(char *name)
{
	int	i;

	i = 6;
	while (name[i] != ' ' && name[i])
		i++;
	if (name[i] == '\0')
		return (0);
	if (!check_quotes(name, i) || ft_strchr(name, '=') != NULL)
		return (take_away_quotes(name), write_error(name),
			write_error(": command not found\n"), ERROR_NOTFOUND);
	return (0);
}

int	ft_unset(char *name, char *str, t_env *env)
{
	int		len;
	t_env	*cur;
	t_env	*tmp;

	if (ft_unset_bis(name) > 0)
		return (ft_unset_bis(name));
	len = ft_strlen(str);
	cur = env;
	while (cur->next)
	{
		if (ft_strncmp(cur->next->value, str, len) == 0)
		{
			if (cur->next->value[len] == '=')
			{
				free(cur->next->value);
				tmp = cur->next;
				cur->next = cur->next->next;
				return (free(tmp), 0);
			}
		}
		cur = cur->next;
	}
	return (0);
}

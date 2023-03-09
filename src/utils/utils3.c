/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:36:33 by valentin          #+#    #+#             */
/*   Updated: 2023/03/01 23:14:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_meta(char *str, int i, char c)
{
	if (str[i] == c && check_quotes(str, i))
		return (1);
	else
		return (0);
}

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/' && str[i] != '.')
			return (1);
		i++;
	}
	if (access(str, X_OK) != 0)
		return (1);
	return (0);
}

int	is_point(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '.')
			return (1);
		i++;
	}
	return (0);
}

int	is_get_env(char *dest, int i)
{
	if (i > 0 && isprint(dest[i]) && dest[i] != '"'
		&& dest[i - 1] == '$' && dest[i] != ' '
		&& dest[i] != '\'' && (!check_quotes1(dest, i - 1, '\'')))
		return (1);
	return (0);
}

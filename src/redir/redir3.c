/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:16:37 by marvin            #+#    #+#             */
/*   Updated: 2023/03/01 22:16:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_redir_error(char *cmd)
{	
	int	i;
	int	y;
	int	j;

	i = 0;
	y = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
		{
			while (cmd[i++] == '<')
				y++;
		}
		else if (cmd[i] == '>')
		{
			while (cmd[i++] == '>')
				j++;
		}
		else
			i++;
	}
	if (y > 2 || j > 2)
		return (1);
	return (0);
}

int	is_here(int i, char *str)
{
	if ((i == 0 && is_meta(str, i, '<') && is_meta(str, i + 1, '<')
			&& (!ft_strchr("<>", str[i + 2]) || str[i + 2] == '\0'))
		|| (i > 0 && !ft_strchr("<>", str[i - 1]) && is_meta(str, i, '<')
			&& is_meta(str, i + 1, '<') && (!ft_strchr("<>", str[i + 2])
				|| str[i + 2] == '\0')))
	{
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:02:08 by valentin          #+#    #+#             */
/*   Updated: 2023/02/15 21:08:29 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	return_file(char *str)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = NULL;
	while (str[i])
	{
		if ((i == 0 && is_meta(str, i, '<') && !ft_strchr("<>", str[i + 1]))
			|| (i > 0 && !ft_strchr("<>", str[i - 1]) && is_meta(str, i, '<')
				&& !ft_strchr("<>", str[i + 1])))
		{
			str2 = return_word(str, i + 1);
			if (is_file(str2))
				break ;
			else
			{
				g_sig.code_error = 1;
				write_perror(str2);
				free_str(str2);
				return (0);
			}
		}
	}
	free_str(str2);
	return (1);
}

void	error_cmd(char *str, char *dest, int type)
{
	g_sig.code_error = 127;
	if (type == 1)
	{
		if (!return_file(str))
			return ;
	}
	if (ft_isprint(dest[0]))
	{
		write_error(dest);
		write_error(": command not found\n");
		return ;
	}
	return ;
}

void	error_cmd_after(char *str)
{
	g_sig.code_error = 127;
	if (ft_isprint(str[0]))
	{
		write_error(str);
		write_error(": command not found\n");
	}
	return ;
}

int	find_cmd_after(char *str, t_data *data)
{
	int		i;
	char	*dest2;

	i = 0;
	dest2 = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
		{
			i = end_word(str, i);
			free_str(dest2);
			dest2 = NULL;
			if (str[i])
				dest2 = return_word(str, i);
			else
				break ;
			if (is_cmd(data->cmd_paths, dest2))
				return (free_str(dest2), 1);
			else
				return (error_cmd_after(dest2), free_str(dest2), 0);
		}
		i++;
	}
	return (free_str(dest2), 0);
}

int	find_cmd(char *str, t_data *data, int type)
{
	int		i;
	char	*dest;

	i = 0;
	dest = NULL;
	dest = return_word(str, i);
	if (is_cmd(data->cmd_paths, dest))
	{
		free_str(dest);
		return (1);
	}
	else
	{
		if (find_cmd_after(str, data))
		{
			free_str(dest);
			return (1);
		}
	}
	error_cmd(str, dest, type);
	free_str(dest);
	return (0);
}

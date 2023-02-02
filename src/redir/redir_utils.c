/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:02:08 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 00:05:06 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	end_word(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '>' || str[i] == '<')
		i++;
	while (str[i] != ' ' && str[i] && str[i] != '>' && str[i] != '<'
		&& str[i] != '"' && str[i] != '\'')
		i++;
	return (i);
}

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
				write_perror(str2);
				free_str(str2);
				return (0);
			}
		}
	}
	free_str(str2);
	return (1);
}

void	error_cmd(char *str, char *dest)
{
	char	*str2;

	str2 = NULL;
	if (!return_file(str))
	{
		free_str(str2);
		return ;
	}
	if (dest != NULL)
	{
		write_error(dest);
		write_error(": command not found\n");
		free_str(str2);
		return ;
	}
	str2 = return_word(str, 0);
	if (str2 != NULL)
	{
		write_error(str2);
		write_error(": command not found\n");
	}
	free_str(str2);
	return ;
}

int	find_cmd_after(char *str, t_data *data, char *dest)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
		{
			i = end_word(str, i);
			free_str(dest);
			dest = NULL;
			if (str[i])
				dest = return_word(str, i);
			else
				break ;
			if (is_cmd(data->cmd_paths, dest))
			{
				free_str(dest);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	find_cmd(char *str, t_data *data)
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
		if (find_cmd_after(str, data, dest))
		{
			free_str(dest);
			return (1);
		}
	}
	error_cmd(str, dest);
	free_str(dest);
	return (0);
}

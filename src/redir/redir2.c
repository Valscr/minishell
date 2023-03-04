/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:22:17 by valentin          #+#    #+#             */
/*   Updated: 2023/03/01 22:18:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_char(char *str, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (check_quotes(str, i))
				j++;
		}
		i++;
	}
	return (j);
}

int	check_redir(char *str)
{
	if (ft_strnstr(str, "<", ft_strlen(str)) && find_char(str, '<'))
		return (1);
	if (ft_strnstr(str, ">", ft_strlen(str)) && find_char(str, '>'))
		return (1);
	if (ft_strnstr(str, "<<", ft_strlen(str)) && find_char(str, '<'))
		return (1);
	if (ft_strnstr(str, ">>", ft_strlen(str)) && find_char(str, '>'))
		return (1);
	return (0);
}

int	end_word(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '>' || str[i] == '<')
		i++;
	while (str[i] != ' ' && str[i] && str[i] != '>' && str[i] != '<'
		&& str[i] != '"' && str[i] != '\'' && str[i] != '\0')
		i++;
	return (i);
}

char	**check_error_redir_init(t_data *data, char *buf)
{
	char	**cmd;

	data->type = 1;
	data->count = 0;
	data->paths = find_path(data->env);
	data->cmd_paths = ft_split(data->paths, ":");
	if (iter_pipe(buf) > 1)
		cmd = ft_split2(buf, "|");
	else
		cmd = ft_split2(buf, "");
	if (!cmd)
		return (write_error("Error malloc\n"), NULL);
	return (cmd);
}

int	check_error_redir(t_data *data, char *buf)
{
	char	**cmd;
	int		error;

	error = 0;
	cmd = check_error_redir_init(data, buf);
	if (!cmd)
		return (0);
	while (cmd[data->count])
	{
		if (check_redir(cmd[data->count]))
		{
			ft_redir(data, cmd[data->count]);
			error = g_sig.code_error;
		}
		else
			error = check_cmd(data, cmd[data->count]);
		data->count++;
	}
	return (free_tab_str(cmd), free_tab_str(data->cmd_paths), error);
}

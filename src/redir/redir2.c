/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:22:17 by valentin          #+#    #+#             */
/*   Updated: 2023/02/28 15:32:57 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_file(char *str, t_data *data, int i, int type)
{
	char	*dest;

	if (data->type == 1)
		return (1);
	dest = return_word(str, i + 1);
	if (ft_strlen(dest) > 0)
	{
		if (type == 1)
			data->outfile = open(dest, O_APPEND | O_CREAT | O_RDWR, 0644);
		else if (type == 2)
			data->outfile = open(dest, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (data->outfile < 0)
		{
			free_str(dest);
			return (0);
		}
		free_str(dest);
		return (1);
	}
	free_str(dest);
	return (0);
}

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

int	check_cmd(t_data *data, char *argv)
{
	char	**cmd_args;
	char	*cmd;
	int		error;

	error = 127;
	cmd_args = ft_split(argv, "  '\"");
	cmd = get_cmd(data->cmd_paths, cmd_args[0]);
	if (!cmd)
	{
		child_free(cmd_args, cmd);
		return (error);
	}
	child_free(cmd_args, cmd);
	return (0);
}

int	check_error_redir(t_data *data, char *buf)
{
	char	**cmd;
	int		error;

	error = 0;
	data->type = 1;
	data->count = 0;
	cmd = NULL;
	data->paths = find_path(data->env);
	data->cmd_paths = ft_split(data->paths, ":");
	if (iter_pipe(buf) > 1)
		cmd = ft_split2(buf, "|");
	else
		cmd = ft_split2(buf, "");
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
	free_tab_str(cmd);
	free_tab_str(data->cmd_paths);
	data->cmd_paths = NULL;
	data->count = 0;
	return (error);
}

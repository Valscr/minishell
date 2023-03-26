/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:02:19 by valentin          #+#    #+#             */
/*   Updated: 2023/03/27 00:15:30 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**parse_error_init(t_data *data, char *buf)
{
	char	**cmd;

	data->type = 1;
	data->count = 0;
	data->paths = find_path(data->env);
	if (!check_pipe(buf))
		return (write_error("syntax error near unexpected token `|'\n"), NULL);
	if (iter_pipe(buf) > 1)
		cmd = ft_split3(buf, "|");
	else
		cmd = ft_split3(buf, "");
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	parse_error(t_data *data, char *buf)
{
	char	**cmd;
	int		error;

	error = 0;
	cmd = parse_error_init(data, buf);
	if (!cmd)
		return (0);
	while (cmd[data->count])
	{
		if (check_redir(cmd[data->count]))
		{
			if (ft_redir(data, cmd[data->count]) > -1)
				error = SUCESS_CODE;
			else
				error = g_sig.code_error;
		}
		else
		{
			check_arg2(cmd[data->count], data, count_tab(cmd));
			error = check_cmd(data, cmd[data->count]);
		}
		data->count++;
	}
	return (free_tab_str(cmd), error);
}

int	check_builtins2(char *argv)
{
	if (ft_strlen(argv) >= 5 && !ft_strncmp(argv, "unset", 5))
	{
		if (ft_strlen(argv) > 5 && argv[5] != ' ')
			return (-1);
		return (g_sig.code_error);
	}
	if (ft_strlen(argv) >= 2 && !ft_strncmp(argv, "cd", 2))
	{
		if (ft_strlen(argv) > 2 && argv[2] != ' ')
			return (-1);
		return (g_sig.code_error);
	}
	if (ft_strlen(argv) >= 3 && !ft_strncmp(argv, "pwd", 3))
	{
		if (ft_strlen(argv) > 3 && argv[3] != ' ')
			return (-1);
		return (g_sig.code_error);
	}
	if (ft_strlen(argv) >= 4 && !ft_strncmp(argv, "exit", 4))
	{
		if (ft_strlen(argv) > 4 && argv[4] != ' ')
			return (-1);
		return (g_sig.code_error);
	}
	return (-1);
}

int	check_builtins(char *argv)
{
	if (ft_strlen(argv) >= 3 && !ft_strncmp(argv, "env", 3))
	{
		if (ft_strlen(argv) > 3 && argv[3] != ' ')
			return (-1);
		return (g_sig.code_error);
	}
	if (ft_strlen(argv) >= 4 && !ft_strncmp(argv, "echo", 4))
	{
		if (ft_strlen(argv) > 4 && argv[4] != ' ')
			return (-1);
		return (g_sig.code_error);
	}
	if (ft_strlen(argv) >= 6 && !ft_strncmp(argv, "export", 6))
	{
		if (ft_strlen(argv) > 6 && argv[6] != ' ')
			return (-1);
		return (g_sig.code_error);
	}
	return (check_builtins2(argv));
}

int	check_cmd(t_data *data, char *argv)
{
	char	**cmd_args;
	char	*cmd;
	int		i;
	int		error;

	error = ERROR_NOTFOUND;
	cmd_args = ft_split2(argv, " ");
	if (!cmd_args)
		return (0);
	cmd = get_cmd(data->cmd_paths, cmd_args[0]);
	i = check_builtins(argv);
	if (i > -1)
		return (child_free(cmd_args, cmd), g_sig.code_error);
	if (!cmd)
	{
		if (!is_slash(cmd_args[0]))
			error = error_slash(cmd_args[0], 1);
		else if (find_slash(cmd_args[0]) && cmd_args[0])
			write_perror(cmd_args[0]);
		else if (is_slash(cmd_args[0]) && cmd_args[0] && cmd_args[0][0] != '\0')
			error_cmdnotfound(cmd_args[0]);
		return (child_free(cmd_args, cmd), error);
	}
	return (child_free(cmd_args, cmd), g_sig.code_error);
}

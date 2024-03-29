/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:02:19 by valentin          #+#    #+#             */
/*   Updated: 2023/03/28 14:13:32 by valentin         ###   ########.fr       */
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
			error = check_cmd(data, cmd[data->count]);
		data->count++;
	}
	return (free_tab_str(cmd), error);
}

int	check_builtins2(char *argv, char *str, int i)
{
	if (ft_strlen(argv) >= 6 && !ft_strncmp(argv, "export", 6))
	{
		if (ft_strlen(argv) > 6 && argv[6] != ' ')
			return (free_str(argv), -1);
		return (free_str(argv), g_sig.code_error);
	}
	if (ft_strlen(argv) >= 5 && !ft_strncmp(argv, "unset", 5)
		&& check_quotes(str, i))
	{
		if (ft_strlen(argv) > 5 && argv[5] != ' ')
			return (free_str(argv), -1);
		return (free_str(argv), g_sig.code_error);
	}
	return (check_builtins3(argv, str, i));
}

int	check_builtins(char *str)
{
	char	*argv;
	int		i;

	argv = ft_strdup(str);
	take_away_quotes(argv);
	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	if (ft_strlen(argv) >= 4 && !ft_strncmp(argv, "echo", 4)
		&& check_quotes(str, i))
	{
		if (ft_strlen(argv) > 4 && argv[4] != ' ')
			return (free_str(argv), -1);
		return (free_str(argv), g_sig.code_error);
	}
	if (ft_strlen(argv) >= 3 && !ft_strncmp(argv, "env", 3)
		&& check_quotes(str, i))
	{
		if (ft_strlen(argv) > 3 && argv[3] != ' ')
			return (free_str(argv), -1);
		return (free_str(argv), g_sig.code_error);
	}
	return (check_builtins2(argv, str, i));
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
	check_arg2(argv, data, iter_pipe(data->argv));
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

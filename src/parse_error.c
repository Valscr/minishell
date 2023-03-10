/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:02:19 by valentin          #+#    #+#             */
/*   Updated: 2023/03/10 14:48:22 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**parse_error_init(t_data *data, char *buf)
{
	char	**cmd;

	data->type = 1;
	data->count = 0;
	data->paths = find_path(data->env);
	if (iter_pipe(buf) > 1)
		cmd = ft_split3(buf, "|");
	else
		cmd = ft_split3(buf, "");
	if (!cmd)
		return (write_error("Error malloc\n"), NULL);
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

int	check_builtins2(char *argv, char *cmd_args)
{
	if (ft_strlen(argv) >= 5 && !ft_strncmp(argv, "unset", 5))
	{
		if (ft_strlen(argv) == 5 || argv[5] == ' ')
			return (g_sig.code_error);
		return (error_cmdnotfound(cmd_args), ERROR_NOTFOUND);
	}
	if (ft_strlen(argv) >= 2 && !ft_strncmp(argv, "cd", 2))
	{
		if (argv[2] != ' ' && argv[2] != '\0')
			return (error_cmdnotfound(cmd_args), ERROR_NOTFOUND);
		return (g_sig.code_error);
	}
	if (ft_strlen(argv) >= 3 && !ft_strncmp(argv, "pwd", 3))
	{
		if (argv[3] != ' ' && argv[3] != '\0')
			return (error_cmdnotfound(cmd_args), ERROR_NOTFOUND);
		return (g_sig.code_error);
	}
	return (-1);
}

int	check_builtins(char *argv, char *cmd_args)
{
	if (ft_strlen(argv) >= 3 && !ft_strncmp(argv, "env", 3))
	{
		if (ft_strlen(argv) == 3 || argv[3] == ' ')
			return (g_sig.code_error);
		return (error_cmdnotfound(cmd_args), ERROR_NOTFOUND);
	}
	if (ft_strlen(argv) >= 4 && !ft_strncmp(argv, "echo", 4))
	{
		if (ft_strlen(argv) == 4 || argv[4] == ' ')
			return (g_sig.code_error);
		return (error_cmdnotfound(cmd_args), ERROR_NOTFOUND);
	}
	if (ft_strlen(argv) >= 6 && !ft_strncmp(argv, "export", 6))
	{
		if (ft_strlen(argv) == 6 || argv[6] == ' ')
			return (g_sig.code_error);
		return (error_cmdnotfound(cmd_args), ERROR_NOTFOUND);
	}
	return (check_builtins2(argv, cmd_args));
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
		return (write_perror("Error malloc\n"));
	cmd = get_cmd(data->cmd_paths, cmd_args[0]);
	i = check_builtins(argv, cmd_args[0]);
	if (i > -1)
		return (child_free(cmd_args, cmd), SUCESS_CODE);
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
	return (child_free(cmd_args, cmd), SUCESS_CODE);
}

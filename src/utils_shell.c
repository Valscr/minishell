/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:01:51 by valentin          #+#    #+#             */
/*   Updated: 2023/03/09 20:53:05 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_empty_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t')
			return (1);
		i++;
	}
	g_sig.code_error = 0;
	return (0);
}

char	*init_shell(void)
{
	char	*dest;
	char	*true;
	char	*false;
	char	*prompt;

	true = ft_strdup("\001\033[1;90m\002○\001\033[0m\002 ");
	if (true == 0)
		return (NULL);
	false = ft_strdup("\001\033[1;31m\002○\001\033[0m\002 ");
	if (false == 0)
		return (NULL);
	prompt = ft_strdup("\001\033[1;94m\002minishell\001\033[0m\002$ ");
	if (prompt == 0)
		return (NULL);
	signal(SIGINT, (void (*)(int))ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	if (g_sig.code_error == 0)
		dest = ft_strjoin(true, prompt);
	else
		dest = ft_strjoin(false, prompt);
	free(true);
	free(false);
	free(prompt);
	return (dest);
}

int	check_builtins2(char *argv, char *cmd_args)
{
	if (ft_strlen(argv) >= 5 && !ft_strncmp(argv, "unset", 5))
	{
		if (ft_strlen(argv) == 5 || argv[5] == ' ')
			return (g_sig.code_error);
		return (error_cmdnotfound(cmd_args), 127);
	}
	if (ft_strlen(argv) >= 2 && !ft_strncmp(argv, "cd", 2))
	{
		if (argv[2] != ' ' && argv[2] != '\0')
			return (error_cmdnotfound(cmd_args), 127);
		return (g_sig.code_error);
	}
	if (ft_strlen(argv) >= 3 && !ft_strncmp(argv, "pwd", 3))
	{
		if (argv[3] != ' ' && argv[3] != '\0')
			return (error_cmdnotfound(cmd_args), 127);
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
		return (error_cmdnotfound(cmd_args), 127);
	}
	if (ft_strlen(argv) >= 4 && !ft_strncmp(argv, "echo", 4))
	{
		if (ft_strlen(argv) == 4 || argv[4] == ' ')
			return (g_sig.code_error);
		return (error_cmdnotfound(cmd_args), 127);
	}
	if (ft_strlen(argv) >= 6 && !ft_strncmp(argv, "export", 6))
	{
		if (ft_strlen(argv) == 6 || argv[6] == ' ')
			return (g_sig.code_error);
		return (error_cmdnotfound(cmd_args), 127);
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
		return (child_free(cmd_args, cmd), i);
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
	return (child_free(cmd_args, cmd), 0);
}

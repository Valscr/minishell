/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:01:51 by valentin          #+#    #+#             */
/*   Updated: 2023/03/01 23:06:20 by marvin           ###   ########.fr       */
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

int	check_cmd(t_data *data, char *argv)
{
	char	**cmd_args;
	char	*cmd;
	int		error;

	error = 127;
	cmd_args = ft_split(argv, "  '\"");
	if (!cmd_args)
		return (write_perror("Error malloc\n"));
	cmd = get_cmd(data->cmd_paths, cmd_args[0]);
	if (!ft_strncmp(argv, "export", 6))
	{
		if (ft_strlen(argv) == 6 || argv[6] == ' ')
			return (child_free(cmd_args, cmd), g_sig.code_error);
		else
			error_cmdnotfound(cmd_args);
		return (child_free(cmd_args, cmd), 127);
	}
	if (!ft_strncmp(argv, "unset", 5))
	{
		if (ft_strlen(argv) == 5 || argv[5] == ' ')
			return (child_free(cmd_args, cmd), g_sig.code_error);
		else
			error_cmdnotfound(cmd_args);
		return (child_free(cmd_args, cmd), 127);
	}
	if (!ft_strncmp(argv, "cd", 2))
		return (child_free(cmd_args, cmd), g_sig.code_error);
	if (!ft_strncmp(argv, "pwd", 3))
		return (child_free(cmd_args, cmd), g_sig.code_error);
	if (!cmd)
	{
		if (!is_slash(cmd_args[0]))
			error = error_slash(cmd_args, 1);
		else if (find_slash(cmd_args[0]) && cmd_args[0])
			write_perror(cmd_args[0]);
		else if (is_slash(cmd_args[0]) && cmd_args[0] && cmd_args[0][0] != '\0')
			error_cmdnotfound(cmd_args);
		return (child_free(cmd_args, cmd), error);
	}
	return (child_free(cmd_args, cmd), 0);
}

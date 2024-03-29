/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:11:25 by valentin          #+#    #+#             */
/*   Updated: 2023/03/27 01:52:56 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_bis(t_data *data, char *cmd, char **cmd_args)
{
	char	**env;

	signal(SIGINT, SIG_DFL);
	env = env_list_to_string_array(data->env);
	execve(cmd, cmd_args, env);
	write_error(cmd);
	write_error(": Is a directory\n");
	free_all(data, cmd_args, cmd, env);
	exit(ERROR_ISDIRECTORY);
}

int	check_builtins_w2(char *argv)
{
	if (ft_strlen(argv) >= 5 && !ft_strncmp(argv, "unset", 5))
	{
		if (ft_strlen(argv) == 5 || argv[5] == ' ')
			return (1);
	}
	if (ft_strlen(argv) >= 2 && !ft_strncmp(argv, "cd", 2))
	{
		if (argv[2] != ' ' && argv[2] != '\0')
			return (1);
	}
	if (ft_strlen(argv) >= 3 && !ft_strncmp(argv, "pwd", 3))
	{
		if (argv[3] != ' ' && argv[3] != '\0')
			return (1);
	}
	return (0);
}

int	check_builtins_w(char *argv)
{
	if (ft_strlen(argv) >= 3 && !ft_strncmp(argv, "env", 3))
	{
		if (ft_strlen(argv) == 3 || argv[3] == ' ')
			return (1);
	}
	if (ft_strlen(argv) >= 4 && !ft_strncmp(argv, "echo", 4))
	{
		if (ft_strlen(argv) == 4 || argv[4] == ' ')
			return (1);
	}
	if (ft_strlen(argv) >= 6 && !ft_strncmp(argv, "export", 6))
	{
		if (ft_strlen(argv) == 6 || argv[6] == ' ')
			return (1);
	}
	return (check_builtins_w2(argv));
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd == NULL || !is_slash(cmd) || !is_point(cmd))
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (!paths)
		return (NULL);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (write_perror("Error malloc\n"), NULL);
		command = ft_strjoin(tmp, cmd);
		free_str(tmp);
		if (!command)
			return (write_perror("Error malloc\n"), NULL);
		if (access(command, X_OK) == 0)
			return (command);
		free_str(command);
		paths++;
	}
	return (NULL);
}

int	iter_pipe(char *argv)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (argv[i++])
	{
		if (argv[i] == '|' && check_quotes(argv, i)
			&& check_empty_pipe(argv, i) && check_empty_bpipe(argv, i))
			j++;
	}
	return (j);
}

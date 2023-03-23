/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 00:21:16 by valentin          #+#    #+#             */
/*   Updated: 2023/03/23 23:04:48 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_fonct(t_data *data, char *argv)
{	
	int	status;
	int	error;
	int	pipe;

	status = 0;
	error = 0;
	pipe = iter_pipe(argv) - 1;
	(void)data;
	(void)pipe;
	if (iter_pipe(argv) > 1)
		close_pipes(data, iter_pipe(argv));
	waitpid(0, &status, 0);
	parent_free(data);
	error = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (ft_putstr_fd("\n", 1), ERROR_CTRLC);
		if (WTERMSIG(status) == 3)
			return (ERROR_CTRLB);
	}
	return (error);
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

int	is_cmd_bis(char **paths, char *cmd)
{
	char	**cmd_args;

	if (cmd == NULL || !is_slash(cmd))
		return (0);
	cmd_args = ft_split2(cmd, " ");
	if (check_builtins_w(cmd))
		return (free_tab_str(cmd_args), 1);
	if (access(cmd, X_OK) == 0)
		return (free_tab_str(cmd_args), 1);
	if (!paths)
		return (free_tab_str(cmd_args), 0);
	return (free_tab_str(cmd_args), -1);
}

int	is_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (is_cmd_bis(paths, cmd) > -1)
		return (is_cmd_bis(paths, cmd));
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (write_perror("Error malloc\n"), 0);
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!command)
			return (write_perror("Error malloc\n"), 0);
		if (access(command, 0) == 0)
		{
			free(command);
			return (1);
		}
		free(command);
		paths++;
	}
	return (0);
}

void	get_dup2(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

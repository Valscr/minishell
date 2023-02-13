/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 00:21:16 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 16:08:32 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_fonct(t_data *data, char *argv)
{	
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (iter_pipe(argv) > 1)
	{
		close_pipes(data, iter_pipe(argv));
		while (i++ < 2 * (iter_pipe(argv) - 1))
			waitpid(0, &status, 0);
		parent_free(data);
	}
	else
		waitpid(0, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	is_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd == NULL || cmd[0] == 0)
		return (0);
	while (*paths)
	{
		if (access(cmd, X_OK) == 0)
			return (1);
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
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

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/')
			return (1);
		i++;
	}
	return (0);
}

void	get_dup2(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:06:13 by valentin          #+#    #+#             */
/*   Updated: 2023/03/01 23:17:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_in_out(char *arg, t_data *d, int redir)
{
	if (redir >= 2 && d->count > 0)
		get_dup2(d->tube[2 * d->count - 2], d->outfile);
	else if (redir >= 2 && d->count == 0)
		get_dup2(d->infile, d->outfile);
	else if (redir == 1 && iter_pipe(arg) - 1 == d->count)
		get_dup2(d->infile, 1);
	else if (redir == 1 && iter_pipe(arg) > 1 && d->count < iter_pipe(arg) - 1)
		get_dup2(d->infile, d->tube[2 * d->count + 1]);
	else if (redir == 0)
	{
		if (d->count == 0)
			get_dup2(d->infile, d->tube[1]);
		else if (d->count == (iter_pipe(arg) - 1))
			get_dup2(d->tube[2 * d->count - 2], 1);
		else
			get_dup2(d->tube[2 * d->count - 2],
				d->tube[2 * d->count + 1]);
	}
	close_pipes(d, iter_pipe(arg));
	return (1);
}

void	process_exec(t_data *data, char *argv)
{
	int	rd;

	rd = 0;
	data->type = 0;
	if (iter_pipe(argv) > 1)
		data->cmd = ft_split2(argv, "|");
	else
		data->cmd = ft_split2(argv, "");
	if (!data->cmd)
		return ;
	if (check_redir(data->cmd[data->count]))
		rd = ft_redir(data, data->cmd[data->count]);
	if (iter_pipe(argv) > 1 || (rd > 0 && data->cmd_redir))
		get_in_out(argv, data, rd);
	if (rd > 0)
		child(data, data->cmd_redir);
	else if (rd == 0)
		child(data, data->cmd[data->count]);
	else
	{
		if (iter_pipe(argv) > 1)
			parent_free(data);
		free_end_process(data);
		exit(g_sig.code_error);
	}
}

int	exec(t_data *data, char *argv)
{
	pid_t	pid;

	if (!init_exec(argv, data))
		return (g_sig.code_error);
	while (data->count < (iter_pipe(argv)))
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			process_exec(data, argv);
		data->count++;
	}
	return (free_tab_str(data->cmd), wait_fonct(data, argv));
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd == NULL || !is_slash(cmd) || !paths)
		return (NULL);
	while (*paths)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (write_perror("Error malloc\n"), NULL);
		command = ft_strjoin(tmp, cmd);
		free_str(tmp);
		if (!command)
			return (write_perror("Error malloc\n"), NULL);
		if (access(command, 0) == 0)
			return (command);
		free_str(command);
		paths++;
	}
	return (NULL);
}

void	child(t_data *data, char *argv)
{
	char	**cmd_args;
	char	*cmd;
	int		error;

	error = 127;
	init_child(data, argv);
	cmd_args = ft_split(argv, "  '\"");
	if (!cmd_args)
		return ;
	cmd = get_cmd(data->cmd_paths, cmd_args[0]);
	if (!cmd)
	{
		if (!is_slash(cmd_args[0]))
			error = error_slash(cmd_args[0], 0);
		free_end_process(data);
		child_free(cmd_args, cmd);
		exit(error);
	}
	signal(SIGINT, SIG_DFL);
	execve(cmd, cmd_args, env_list_to_string_array(data->env));
	exit(127);
	return ;
}

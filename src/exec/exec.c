/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:06:13 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 03:51:17 by valentin         ###   ########.fr       */
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

void	process_exec(t_data *data, char *argv, t_env **env)
{
	int	rd;

	rd = 0;
	data->cmd = ft_split2(argv, "|");
	if (check_redir(data->cmd[data->count]))
		rd = ft_redir(data);
	if (iter_pipe(argv) > 1 || (rd > 0 && data->cmd_redir))
		get_in_out(argv, data, rd);
	if (rd > 0)
		child(data, data->cmd_redir, env);
	else if (rd == 0)
		child(data, data->cmd[data->count], env);
	else
	{
		if (iter_pipe(argv) > 1)
			parent_free(data);
		free_end_process(data);
		exit (127);
	}
	return ;
}

int	exec(t_data *data, char *argv, t_env **env)
{
	if (!init_exec(argv, data))
		return (0);
	while (data->count < (iter_pipe(argv)))
	{
		g_sig.pid = fork();
		if (g_sig.pid == 0)
			process_exec(data, argv, env);
		data->count++;
	}
	return (free_tab_str(data->cmd), wait_fonct(data, argv));
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd == NULL || !is_slash(cmd))
		return (NULL);
	while (*paths)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	child(t_data *data, char *argv, t_env **env)
{
	char	**cmd_args;
	char	*cmd;
	int		error;

	error = 127;
	init_child(data, argv);
	cmd_args = ft_split(argv, "  '\"");
	cmd = get_cmd(data->cmd_paths, cmd_args[0]);
	if (!cmd)
	{
		if (!is_slash(cmd_args[0]))
			error = error_slash(cmd_args);
		else if (find_slash(cmd_args[0]) && cmd_args[0])
			write_perror(cmd_args[0]);
		else if (is_slash(cmd_args[0]) && cmd_args[0] && cmd_args[0][0] != '\0')
			error_cmdnotfound(cmd_args);
		free_end_process(data);
		child_free(cmd_args, cmd);
		exit(error);
	}
	execve(cmd, cmd_args, env_list_to_string_array(*env));
	exit (127);
	return ;
}

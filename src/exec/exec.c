/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:06:13 by valentin          #+#    #+#             */
/*   Updated: 2023/02/12 22:04:04 by valentin         ###   ########.fr       */
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

int	exec(t_data *data, char *argv, t_env **env)
{
	int		rd;

	if (iter_pipe(argv) > 1)
	{
		data->tube = malloc(sizeof(int) * (2 * (iter_pipe(argv) - 1)));
		if (!get_pipes(data, argv))
			return (write_error("Error\n"));
	}
	signal(SIGQUIT, (void (*)(int))sig_quit);
	while (data->count < (iter_pipe(argv)))
	{
		rd = 0;
		g_sig.pid = fork();
		if (g_sig.pid == 0)
		{	
			data->cmd = ft_split2(argv, "|");
			if (check_redir(data->cmd[data->count]))
			{
				init_redir(data);
				rd = ft_redir(data);
			}
			if (iter_pipe(argv) > 1 || (rd > 0 && data->cmd_redir[data->count]))
				get_in_out(argv, data, rd);
			if (rd > 0)
				child(data, data->cmd_redir[data->count], env);
			else if (rd == 0)
				child(data, data->cmd[data->count], env);
			else
			{
				if (iter_pipe(argv) > 1)
					parent_free(data);
				free_end_process(data);
				exit (127);
			}
		}
		data->count++;
	}
	return (free_tab_str(data->cmd), wait_fonct(data, argv));
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

int	is_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd == NULL || cmd[0] == 0 )
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

int	find_slash(char *str)
{
	int	i;	

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	child(t_data *data, char *argv, t_env **env)
{
	char	**cmd_args;
	char	*cmd;

	if (data->tube != NULL)
		parent_free(data);
	if (argv == NULL)
	{
		free_end_process(data);
		exit(0);
	}
	check_arg(argv, data);
	cmd_args = ft_split(argv, "  '\"");
	cmd = get_cmd(data->cmd_paths, cmd_args[0]);
	if (!cmd)
	{
		if (!is_slash(cmd_args[0]))
		{
			write(2, cmd_args[0], ft_strlen(cmd_args[0]));
			write(2, ": Is a directory\n", 18);
			free_end_process(data);
			child_free(cmd_args, cmd);
			exit (126);
		}
		else if (find_slash(cmd_args[0]) && cmd_args[0] && cmd_args[0][0] != '\0')
			write_perror(cmd_args[0]);
		else if (is_slash(cmd_args[0]) && cmd_args[0] && cmd_args[0][0] != '\0')
		{
			write(2, cmd_args[0], ft_strlen(cmd_args[0]));
			write(2, ": command not found\n", 21);
		}
		free_end_process(data);
		child_free(cmd_args, cmd);
		exit(127);
	}
	execve(cmd, cmd_args, env_list_to_string_array(*env));
	exit (127);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:18 by vescaffr          #+#    #+#             */
/*   Updated: 2023/03/01 23:13:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sig	g_sig;

int	loop_pipe(t_data data, char *argv)
{
	int	error;

	if (argv[0] == 0)
		return (0);
	if (!argv || !argv[0])
		data.argv = NULL;
	else
		data.argv = get_env(argv, &data);
	if (!data.argv)
		return (0);
	data.paths = find_path(data.env);
	data.cmd_paths = ft_split(data.paths, ":");
	if (!data.cmd_paths)
		return (0);
	if (limiter_heredoc(data.argv, &data) != 2)
		error = exec(&data, data.argv);
	else
		error = 130;
	free_str(data.argv);
	free_tab_str(data.cmd_paths);
	return (error);
}

void	execute(char *buf, t_data *data)
{
	if (check_empty_line(buf))
	{
		add_history(buf);
		data->type = 0;
		g_sig.code_error = loop_pipe(*data, buf);
		check_arg2(buf, data);
		if (g_sig.code_error != 130 && g_sig.code_error != 131
			&& g_sig.code_error != 2)
		{
			g_sig.code_error = check_error_redir(data, buf);
		}
		data->limiter = 0;
	}
	write(data->file, buf, ft_strlen(buf));
	write(data->file, "\n", 1);
	return ;
}

int	loop_shell(t_data *data)
{
	char	*buf;
	int		i;
	char	*prompt;

	buf = NULL;
	i = 0;
	while (1)
	{
		prompt = init_shell();
		buf = readline(prompt);
		if (buf == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (!ft_strncmp("exit", buf, 4))
		{
			i = check_exit(buf);
			break ;
		}
		free_str(prompt);
		execute(buf, data);
		free_str(buf);
	}
	return (free_str(prompt), free_str(buf), i);
}

int	shell(t_data *data)
{
	data->file = open(".minishell_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->file < 0)
		return (0);
	g_sig.code_error = loop_shell(data);
	close(data->file);
	data->infile = open(".minishell_tmp", O_RDONLY);
	if (data->infile < 0)
		unlink(".heredoc_tmp");
	clear_history();
	return (1);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	if (argc > 1 || argv[1] != NULL)
		return (0);
	if (!init(&data, envp))
		return (0);
	if (!shell(&data))
		return (0);
	free_t_env_list(data.env);
	return (g_sig.code_error);
}

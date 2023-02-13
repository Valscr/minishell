/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:18 by vescaffr          #+#    #+#             */
/*   Updated: 2023/02/13 15:35:55 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sig	g_sig;

int	loop_pipe(t_data data, char *argv)
{
	int	error;

	if (argv[0] == 0)
		return (0);
	data.argv = get_env(argv, &data);
	data.paths = find_path(data.env);
	data.cmd_paths = ft_split(data.paths, ":");
	if (limiter_heredoc(data.argv, &data) != 2)
		error = exec(&data, data.argv, &data.env);
	else
		error = 130;
	data.count = 0;
	free_tab_str(data.cmd_paths);
	free_str(data.argv);
	data.limiter = 0;
	return (error);
}

void	execute(char *buf, t_data *data)
{
	if (check_empty_line(buf))
	{
		add_history(buf);
		g_sig.code_error = loop_pipe(*data, buf);
		check_arg2(buf, data);
	}
	write(data->file, buf, ft_strlen(buf));
	write(data->file, "\n", 1);
	return ;
}

int	loop_shell(t_data *data)
{
	char	*buf;
	int		i;

	buf = NULL;
	i = 0;
	while (1)
	{
		init_shell();
		buf = readline("\001\033[1;94m\002minishell\001\033[0m\002$ ");
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
		execute(buf, data);
		free_str(buf);
	}
	return (free_str(buf), i);
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
	init(&data, envp);
	if (!shell(&data))
		return (0);
	free_tab_str(data.cmd_paths);
	free_t_env_list(data.env);
	return (g_sig.code_error);
}

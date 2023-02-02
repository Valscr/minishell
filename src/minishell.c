/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:18 by vescaffr          #+#    #+#             */
/*   Updated: 2023/02/02 22:26:53 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sig	g_sig;

int	loop_pipe(t_data data, char *argv)
{
	int	error;

	if (argv[0] == 0)
		return (0);
	if (iter_pipe(argv) > 1)
	{
		data.tube = malloc(sizeof(int) * (2 * (iter_pipe(argv) - 1)));
		if (!get_pipes(&data, argv))
			return (write_error("Error\n"));
	}
	argv = get_env(argv, &data);
	data.cmd = ft_split2(argv, "|");
	data.paths = find_path(data.env);
	data.cmd_paths = ft_split(data.paths, ":");
	error = exec(&data, argv, &data.env);
	data.count = 0;
	free(argv);
	free_tab_str(data.cmd_paths);
	if (g_sig.sigint)
		return (g_sig.code_error);
	return (error);
}

int	loop_shell(t_data *data)
{
	char	*buf;

	buf = NULL;
	while (1)
	{
		signal(SIGINT, (void (*)(int))ctrl_c_handler);
		g_sig.pid = 0;
		buf = readline("\033[1;94mminishell\033[0m$ ");
		add_history(buf);
		if (buf == NULL)
		{
			ft_putstr_fd("exit", 1);
			ft_putstr_fd("\n", 1);
			exit(128);
		}
		if (!ft_strncmp("exit", buf, 5))
			break ;
		check_arg2(buf, data);
		g_sig.code_error = loop_pipe(*data, buf);
		g_sig.sigint = 0;
		write(data->file, buf, ft_strlen(buf));
		write(data->file, "\n", 1);
		free_str(buf);
	}
	return (free_str(buf), 1);
}

int	shell(t_data *data)
{
	data->file = open(".minishell_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->file < 0)
		return (0);
	loop_shell(data);
	close(data->file);
	data->infile = open(".minishell_tmp", O_RDONLY);
	if (data->infile < 0)
		unlink(".heredoc_tmp");
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
	return (0);
}

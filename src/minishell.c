/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:18 by vescaffr          #+#    #+#             */
/*   Updated: 2023/03/20 03:31:16 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sig	g_sig;

int	loop_pipe(t_data data, char *argv)
{
	int	error;

	if (!argv || !argv[0])
		data.argv = NULL;
	else
		data.argv = get_env(argv, &data);
	data.paths = find_path(data.env);
	data.cmd_paths = ft_split(data.paths, ":");
	if (limiter_heredoc(data.argv, &data, -1) != 2)
		error = exec(&data, data.argv);
	else
		error = ERROR_CTRLC;
	g_sig.code_error = error;
	if (g_sig.code_error != ERROR_CTRLC && g_sig.code_error != ERROR_CTRLB)
	{
		error = parse_error(&data, data.argv);
	}
	data.limiter = 0;
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
	}
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
		if (!ft_strncmp("exit", buf, 4) && (buf[4] == ' ' || buf[4] == '\0'))
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

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	if (argc > 1 || argv[1] != NULL)
		return (0);
	if (!init(&data, envp))
		return (0);
	g_sig.code_error = loop_shell(&data);
	clear_history();
	free_t_env_list(data.env);
	return (g_sig.code_error);
}

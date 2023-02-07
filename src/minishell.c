/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:18 by vescaffr          #+#    #+#             */
/*   Updated: 2023/02/07 13:49:38 by valentin         ###   ########.fr       */
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
	data.argv = get_env(argv, &data);
	data.paths = find_path(data.env);
	data.cmd_paths = ft_split(data.paths, ":");
	error = exec(&data, data.argv, &data.env);
	data.count = 0;
	g_sig.autorize = 0;
	free_tab_str(data.cmd_paths);
	free_str(data.argv);
	if (g_sig.sigint || g_sig.sigquit)
		return (g_sig.code_error);
	return (error);
}

int	check_empty_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	loop_shell(t_data *data)
{
	char	*buf;

	buf = NULL;
	while (1)
	{
		signal(SIGINT, (void (*)(int))ctrl_c_handler);
		signal(SIGQUIT, SIG_IGN);
		g_sig.pid = 0;
		ft_putstr_fd("\b\b", 1);
		buf = readline("\001\033[1;94m\002minishell\001\033[0m\002$ ");
		if (buf == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (!ft_strncmp("exit", buf, 5))
			break ;
		check_arg2(buf, data);
		g_sig.code_error = loop_pipe(*data, buf);
		g_sig.sigint = 0;
		g_sig.sigquit = 0;
		write(data->file, buf, ft_strlen(buf));
		write(data->file, "\n", 1);
		if (check_empty_line(buf))
			add_history(buf);
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
	clear_history();
	return (1);
}

void	free_t_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current->next != NULL)
	{
		next = current->next;
		if (current->value)
			free_str(current->value);
		free(current);
		current = next;
	}
	free(next);
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
	return (0);
}

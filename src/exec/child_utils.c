/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:39:57 by valentin          #+#    #+#             */
/*   Updated: 2023/03/09 14:28:33 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	init_child(t_data *data, char *argv)
{
	if (data->tube != NULL)
		parent_free(data);
	if (argv == NULL)
	{
		free_end_process(data);
		exit(0);
	}
	check_arg(argv, data);
}

int	error_slash(char *cmd_args, int type)
{
	if ((cmd_args[0] == '.' && cmd_args[1] == '\0'))
	{
		write(STDERR, ".: filename argument required\n", 31);
		return (ERROR_SYNTAX);
	}
	if (cmd_args[0] == '.' && cmd_args[1] == '.' && cmd_args[2] == '\0')
	{
		write(STDERR, cmd_args, ft_strlen(cmd_args));
		write(STDERR, ": command not found\n", 21);
		return (ERROR_NOTFOUND);
	}
	if (type == 1)
	{
		write(STDERR, cmd_args, ft_strlen(cmd_args));
		write(STDERR, ": Is a directory\n", 18);
	}
	return (ERROR_ISDIRECTORY);
}

void	error_cmdnotfound(char *cmd_args)
{
	write(STDERR, cmd_args, ft_strlen(cmd_args));
	write(STDERR, ": command not found\n", 21);
}

int	init_exec(char *argv, t_data *data)
{
	data->count = 0;
	if (!check_pipe(argv))
	{
		g_sig.code_error = ERROR_SYNTAX;
		return (write_error("syntax error near unexpected token `|'\n"));
	}
	if (iter_pipe(argv) > 1)
	{
		data->tube = malloc(sizeof(int) * (2 * (iter_pipe(argv) - 1)));
		if (!get_pipes(data, argv))
			return (write_error("Error\n"));
	}
	signal(SIGQUIT, (void (*)(int))sig_quit);
	return (1);
}

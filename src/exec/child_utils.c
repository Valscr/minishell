/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:39:57 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 03:06:49 by valentin         ###   ########.fr       */
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

int	error_slash(char **cmd_args)
{
	write(2, cmd_args[0], ft_strlen(cmd_args[0]));
	write(2, ": Is a directory\n", 18);
	return (126);
}

void	error_cmdnotfound(char **cmd_args)
{
	write(2, cmd_args[0], ft_strlen(cmd_args[0]));
	write(2, ": command not found\n", 21);
}

int	init_exec(char *argv, t_data *data)
{
	if (iter_pipe(argv) > 1)
	{
		data->tube = malloc(sizeof(int) * (2 * (iter_pipe(argv) - 1)));
		if (!get_pipes(data, argv))
			return (write_error("Error\n"));
	}
	signal(SIGQUIT, (void (*)(int))sig_quit);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:02:19 by valentin          #+#    #+#             */
/*   Updated: 2023/03/09 23:03:57 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**parse_error_init(t_data *data, char *buf)
{
	char	**cmd;

	data->type = 1;
	data->count = 0;
	data->paths = find_path(data->env);
	if (iter_pipe(buf) > 1)
		cmd = ft_split3(buf, "|");
	else
		cmd = ft_split3(buf, "");
	if (!cmd)
		return (write_error("Error malloc\n"), NULL);
	return (cmd);
}

int	parse_error(t_data *data, char *buf)
{
	char	**cmd;
	int		error;

	error = 0;
	cmd = parse_error_init(data, buf);
	if (!cmd)
		return (0);
	while (cmd[data->count])
	{
		if (check_redir(cmd[data->count]))
		{
			ft_redir(data, cmd[data->count]);
			error = g_sig.code_error;
		}
		else
			error = check_cmd(data, cmd[data->count]);
		data->count++;
	}
	return (free_tab_str(cmd), error);
}

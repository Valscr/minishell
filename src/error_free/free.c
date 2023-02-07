/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:20:06 by valentin          #+#    #+#             */
/*   Updated: 2023/02/07 13:53:31 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_free(char **cmd_args, char *cmd)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
	free(cmd);
}

int	free_tab_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != NULL)
	{
		free_str(str[i++]);
	}
	free(str);
	return (0);
}

void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
}

void	free_all(t_data *data)
{
	free_tab_str(data->cmd);
	free_tab_str(data->cmd_tab);
}

void	free_end_process(t_data *data)
{
	free_tab_str(data->cmd);
	free_tab_str(data->cmd_redir);
	free_tab_str(data->cmd_paths);
	free_t_env_list(data->env);
	free_str(data->argv);
	return ;
}

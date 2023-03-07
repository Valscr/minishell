/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:20:06 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 03:27:29 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_free(char **cmd_args, char *cmd)
{	
	free_tab_str(cmd_args);
	if (cmd)
		free_str(cmd);
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
	if (!str)
		return (0);
	free(str);
	return (0);
}

void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
}

void	free_all(t_data *data, char **cmd_args, char *cmd)
{
	free_end_process(data);
	child_free(cmd_args, cmd);
}

void	free_end_process(t_data *data)
{
	free_tab_str(data->cmd);
	free_str(data->cmd_redir);
	free_tab_str(data->cmd_paths);
	free_t_env_list(data->env);
	free_str(data->argv);
	return ;
}

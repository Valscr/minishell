/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:11:25 by valentin          #+#    #+#             */
/*   Updated: 2023/03/09 13:12:09 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_bis(t_data *data, char *cmd, char **cmd_args)
{
	char	**env;

	signal(SIGINT, SIG_DFL);
	env = env_list_to_string_array(data->env);
	execve(cmd, cmd_args, env);
	free_all(data, cmd_args, cmd, env);
	exit(ERROR_NOTFOUND);
}

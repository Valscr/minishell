/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 00:21:16 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 00:52:21 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_fonct(t_data *data, char *argv)
{	
	int	i;
	int	red;
	int	status;

	i = 0;
	red = 0;
	if (iter_pipe(argv) > 1)
	{
		close_pipes(data, iter_pipe(argv));
		while (i++ < 2 * (iter_pipe(argv) - 1))
			waitpid(g_sig.pid, &status, 0);
		parent_free(data);
	}
	else
		waitpid(g_sig.pid, &status, 0);
	if (WIFEXITED(status))
	{
		red = WEXITSTATUS(status);
		return (red);
	}
	return (0);
}

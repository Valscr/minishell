/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:11:33 by valentin          #+#    #+#             */
/*   Updated: 2023/02/12 19:40:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_pipes(t_data *data, char *argv)
{
	int	i;

	i = 0;
	while (i < (iter_pipe(argv) - 1))
	{
		if (pipe(data->tube + 2 * i) < 0)
		{
			parent_free(data);
			return (0);
		}
		i++;
	}
	return (1);
}

void	get_dup2(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	parent_free(t_data *data)
{
	if (data->tube)
	{
		free(data->tube);
		data->tube = NULL;
	}
}

void	close_pipes(t_data *data, int len)
{
	int	i;

	i = 0;
	while (i < (2 * (len - 1)))
		close(data->tube[i++]);
}

int	iter_pipe(char *argv)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (argv[i++])
	{
		if (argv[i] == '|' && check_quotes(argv, i))
			j++;
	}
	return (j);
}

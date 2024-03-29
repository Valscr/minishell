/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:11:33 by valentin          #+#    #+#             */
/*   Updated: 2023/03/27 01:54:36 by valentin         ###   ########.fr       */
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

void	close_pipes(t_data *data, int len)
{
	int	i;

	i = 0;
	while (i < (2 * (len - 1)))
		close(data->tube[i++]);
	parent_free(data);
}

int	check_empty_pipe(char *argv, int i)
{
	i++;
	while (argv[i] == ' ')
		i++;
	if (argv[i] == '|' || argv[i] == '\0')
		return (0);
	return (1);
}

int	check_empty_bpipe(char *argv, int i)
{
	if (i == 0)
		return (0);
	i--;
	while (argv[i] == ' ' && i > 0)
		i--;
	if (i <= 0 || argv[i] == '|')
		return (0);
	return (1);
}

int	check_pipe(char *argv)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (argv[i])
	{
		if (argv[i] == '|' && check_quotes(argv, i)
			&& check_empty_pipe(argv, i))
			j++;
		if (argv[i] == '|' && (!check_empty_pipe(argv, i)
				|| !check_empty_bpipe(argv, i)))
			return (0);
		i++;
	}
	return (j);
}

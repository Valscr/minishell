/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 02:39:45 by valentin          #+#    #+#             */
/*   Updated: 2023/03/12 01:28:00 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	write_error(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		write(STDERR, &str[i++], 1);
	return (0);
}

int	write_perror(char *str)
{
	perror(str);
	return (0);
}

void	error_syntax(t_data *data)
{
	if (data->type)
		write(STDERR, "syntax error\n", 14);
	g_sig.code_error = ERROR_SYNTAX;
	return ;
}

void	parent_free(t_data *data)
{
	if (data->tube)
	{
		free(data->tube);
		data->tube = NULL;
	}
}

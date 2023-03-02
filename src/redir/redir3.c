/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:16:37 by marvin            #+#    #+#             */
/*   Updated: 2023/03/01 22:16:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_file(char *str, t_data *data, int i, int type)
{
	char	*dest;

	if (data->type == 1)
		return (1);
	dest = return_word(str, i + 1);
	if (ft_strlen(dest) > 0)
	{
		if (type == 1)
			data->outfile = open(dest, O_APPEND | O_CREAT | O_RDWR, 0644);
		else if (type == 2)
			data->outfile = open(dest, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (data->outfile < 0)
		{
			free_str(dest);
			return (0);
		}
		free_str(dest);
		return (1);
	}
	free_str(dest);
	return (0);
}

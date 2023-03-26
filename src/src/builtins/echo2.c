/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:52:59 by marvin            #+#    #+#             */
/*   Updated: 2023/03/17 22:52:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_string_n_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == ' ')
		i++;
	if (str[i] != '-')
		return (0);
	if (str[i] == '-' && str[i + 1] != 'n')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else if (str[i] == '\t')
			return (0);
		else if (str[i] == ' ')
			return (i);
		else
			return (0);
	}
	return (i);
}

int	n_option(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (res)
	{
		res = (check_string_n_option(str + i));
		if (res)
			i += res;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:00:08 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 02:05:26 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_number(char	*str)
{
	int	i;

	i = 0;
	if (str[i] != '+' && str[i] != '-' && !ft_isdigit(str[i]))
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_exit(char *str)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = 5;
	if (ft_strlen(str) < 6)
		return (0);
	dest = malloc(sizeof(char) * (ft_strlen(str) - 5 + 1));
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	if (is_number(dest))
	{
		i = ft_atoi(dest);
		free(dest);
		return (i);
	}
	free(dest);
	return (2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:49:26 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 15:45:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes_before(char *str, int j, char c)
{
	int	count;

	count = 0;
	while (j >= 0)
	{
		if (str[j] == c)
			count++;
		j--;
	}
	return (count);
}

int	check_quotes1(char *str, int i, char c)
{
	int	j;
	int	y;

	y = 0;
	j = i;
	while (str[i])
	{
		if (str[i] == c)
		{
			y++;
			break ;
		}
		i++;
	}
	y += check_quotes_before(str, j, c);
	if (y % 2 == 0 && y >= 2)
		return (1);
	return (0);
}

int	check_quotes(char *str, int i)
{
	if (check_quotes1(str, i, '\'') || check_quotes1(str, i, '"'))
		return (0);
	return (1);
}

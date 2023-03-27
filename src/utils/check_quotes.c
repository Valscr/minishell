/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:49:26 by valentin          #+#    #+#             */
/*   Updated: 2023/03/27 12:36:12 by valentin         ###   ########.fr       */
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
	if (y == 0)
		return (0);
	y += check_quotes_before(str, j, c);
	if (y % 2 == 0 && y >= 2 && check_quotes_before(str, j - 1, c) > 0)
		return (1);
	return (0);
}

int	check_quotes(char *str, int i)
{
	if (check_quotes1(str, i, '\'') || check_quotes1(str, i, '"'))
		return (0);
	return (1);
}

int	check_quotes2(char const *str, int i)
{
	if (check_quotes1((char *)str, i, '\'')
		|| check_quotes1((char *)str, i, '"'))
		return (1);
	return (0);
}

void	take_away_quotes(char *s)
{
	int	i;
	int	j;
	int	simpleq;
	int	doubleq;

	i = 0;
	j = 0;
	simpleq = 0;
	doubleq = 0;
	while (s[i])
	{
		if (tests_quotes(s, &i, &simpleq, &doubleq))
			continue ;
		if (s[i] == ' ' && s[i + 1] == ' ' && !simpleq && !doubleq)
			i++;
		else
			s[j++] = s[i++];
	}
	s[j] = '\0';
}

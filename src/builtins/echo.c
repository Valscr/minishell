/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:13:31 by valentin          #+#    #+#             */
/*   Updated: 2023/03/27 09:38:02 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tests_quotes(char *s, int *i, int *simpleq, int *doubleq)
{
	if ((s[*i] == '\'' && *simpleq) || (s[*i] == '\''
			&& !(*simpleq) && !(*doubleq)))
	{
		*simpleq = !(*simpleq);
		(*i)++;
		return (1);
	}
	if ((s[*i] == '\"' && *doubleq) || (s[*i] == '\"'
			&& !(*simpleq) && !(*doubleq)))
	{
		*doubleq = !(*doubleq);
		(*i)++;
		return (1);
	}
	return (0);
}

void	take_away_quotes_echo(char *s)
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
		else if (s[i] == 'n' && s[i + 1] == ' ' && (simpleq || doubleq))
			s[i + 1] = '\t';
		else
			s[j++] = s[i++];
	}
	s[j] = '\0';
}

static int	check_end_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char *str)
{
	int		i;
	int		n;
	int		space;

	space = check_end_space(str);
	take_away_quotes_echo(str);
	n = n_option(str);
	i = n;
	if (str[i] == ' ')
			i++;
	while (str[i])
	{
		if (str[i] == '\t')
			write(STDOUT, " ", 1);
		else if (str[i] == ' ' && str[i + 1] == '\0' && space)
			break ;
		else
			write(STDOUT, str + i, 1);
		i++;
	}
	if (n == 0)
		write(STDOUT, "\n", 1);
	return (0);
}

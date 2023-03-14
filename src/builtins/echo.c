/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:13:31 by valentin          #+#    #+#             */
/*   Updated: 2023/03/14 19:01:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_string_n_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
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

static int	tests_quotes(char *s, int *i, int *simpleq, int *doubleq)
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

static void	take_away_quotes_echo(char *s)
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

int	ft_echo(char *str)
{
	int		i;
	int		n;

	take_away_quotes_echo(str);
	n = n_option(str);
	i = n;
	//printf("--------%d----%s\n", n, str + n);
	printf("--%d---%c\n", i, str[i+1]);
	while (str[i])
	{
		if (str[i] == '\t')
			write(STDOUT, " ", 1);
		else
			write(STDOUT, str + i, 1);
		i++;
	}
	if (n == 0)
		write(STDOUT, "\n", 1);
	return (0);
}

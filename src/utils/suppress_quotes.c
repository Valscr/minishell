/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppress_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:42:29 by marvin            #+#    #+#             */
/*   Updated: 2023/03/13 17:42:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		s[j++] = s[i++];
	}
	s[j] = '\0';
}

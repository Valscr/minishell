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

/*char	*take_away_quotes(char *s)
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
	return (s);
}
*/
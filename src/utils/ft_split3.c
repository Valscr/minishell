/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:36:01 by vescaffr          #+#    #+#             */
/*   Updated: 2023/03/11 22:55:25 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_filldest3(char const *s, int i, int j)
{
	char	*dest;
	int		n;

	n = 0;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (0);
	j = j - i;
	while (i > 0)
	{
		dest[n++] = s[j++];
		i--;
	}
	dest[n] = '\0';
	return (dest);
}

char	**malloc_split(char const *s, char const *sep)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_countdest2(s, sep) + 1));
	if (!dest)
		return (NULL);
	return (dest);
}

char	**ft_split3(char const *s, char const *sep)
{
	char	**dest;
	int		j;
	int		i;
	int		n;

	i = 0;
	j = 0;
	dest = malloc_split(s, sep);
	if (!dest)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == ' ' && s[i])
			i++;
		n = i;
		while (s[i] != '\0' && (!ft_strchr(sep, s[i])
				|| (ft_strchr(sep, s[i]) && check_quotes2(s, i))))
			i++;
		if (i != 0)
			dest[j++] = ft_filldest3(s, i - n, i);
		while (ft_strchr(sep, s[i]) && !check_quotes2(s, i) && s[i] != '\0')
			i++;
	}
	dest[j] = NULL;
	return (dest);
}

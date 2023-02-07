/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:05:54 by valentin          #+#    #+#             */
/*   Updated: 2023/02/06 12:52:44 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_strlen1(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	check_end(char *dest)
{
	int	j;

	j = 0;
	if (!dest)
		return (1);
	while (dest[j] != '\0')
	{
		if (dest[j] == '\n')
			return (0);
		j++;
	}
	return (1);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	int		size;
	int		i;
	char	*dest;
	int		j;

	i = 0;
	size = ft_strlen1(s1) + ft_strlen1(s2) + 1;
	dest = malloc(sizeof(char) * size);
	if (!dest || !s2)
		return (NULL);
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{	
			dest[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j] != '\0')
		dest[i++] = s2[j++];
	dest[i] = '\0';
	if (s1)
		free(s1);
	return (dest);
}

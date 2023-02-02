/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 00:19:44 by vescaffr          #+#    #+#             */
/*   Updated: 2023/01/13 00:03:14 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

/*char *ft_strjoin(char const *s1, char const *s2)
{
	char *dest;
	int i;
	int j;

	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		dest[j] = s2[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	int		i;
	char	*dest;
	int		j;

	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = malloc(sizeof(char) * size);
	if (!dest)
		return (0);
	if (s1)
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
	return (dest);
}

/*int	main()
{
	const char s1[100] = "tripouille";
	const char s2[100] = "42";
	printf("%s\n", ft_strjoin(s1, s2));
	printf("%lu\n", strlen(ft_strjoin(s1, s2)));
	printf("%lu\n", strlen(s1));
	printf("%lu\n", strlen(s2));
}*/

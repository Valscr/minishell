/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:36:01 by vescaffr          #+#    #+#             */
/*   Updated: 2023/02/11 12:58:22 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_countdest(char const *s, char const *sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s[i])
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && !ft_strchr(sep, s[i]))
			i++;
		if (s[i] != '\0' && ft_strchr(sep, s[i]))
		{
			while (ft_strchr(sep, s[i]) && s[i] != '\0')
				i++;
			j++;
		}
	}
	if (!ft_strchr(sep, s[0]) && s[0] != '\0')
		j++;
	if (ft_strchr(sep, s[i - 1]))
		j--;
	return (j);
}

static char	*ft_filldest(char const *s, int i, int j)
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

char	**ft_split(char const *s, char const *sep)
{
	char	**dest;
	int		j;
	int		i;
	int		n;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	dest = malloc(sizeof(char *) * (ft_countdest(s, sep) + 1));
	if (!dest)
		return (0);
	while (s[i] != '\0')
	{
		n = i;
		while (!ft_strchr(sep, s[i]) && s[i] != '\0')
			i++;
		if (i != 0)
			dest[j++] = ft_filldest(s, i - n, i);
		while (ft_strchr(sep, s[i]) && s[i] != '\0')
			i++;
	}
	dest[j] = NULL;
	return (dest);
}	

/*int	main()
{
	char str[] = "";
	char c = 'z';
	printf("%s", ft_split(str, c)[0]);
	printf("\n");
	printf("%s", ft_split(str, c)[1]);
        printf("\n");
	printf("%s", ft_split(str, c)[2]);
        printf("\n");
	printf("%s", ft_split(str, c)[3]);
        printf("\n");
	printf("%s", ft_split(str, c)[4]);
        printf("\n");
	printf("%s", ft_split(str, c)[5]);
        printf("\n");
}*/

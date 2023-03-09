/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:36:01 by vescaffr          #+#    #+#             */
/*   Updated: 2023/03/09 21:03:14 by valentin         ###   ########.fr       */
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

char	**ft_split3(char const *s, char const *sep)
{
	char	**dest;
	int		j;
	int		i;
	int		n;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	dest = malloc(sizeof(char *) * (ft_countdest2(s, sep) + 1));
	if (!dest)
		return (0);
	while (s[i] != '\0')
	{
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

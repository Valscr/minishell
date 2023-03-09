/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:36:01 by vescaffr          #+#    #+#             */
/*   Updated: 2023/03/09 20:42:36 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_char2(char const *str, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (!check_quotes2(str, i))
				j++;
		}
		i++;
	}
	return (j);
}

int	ft_countdest2(char const *s, char const *sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s[i])
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && (!ft_strchr(sep, s[i])
				|| (ft_strchr(sep, s[i]) && check_quotes2(s, i))))
			i++;
		if (s[i] != '\0' && ft_strchr(sep, s[i]) && !check_quotes2(s, i))
		{
			while (ft_strchr(sep, s[i]) && !check_quotes2(s, i) && s[i] != '\0')
				i++;
			j++;
		}
	}
	if (s[0] != '\0' && (!ft_strchr(sep, s[0])
			|| (ft_strchr(sep, s[i - 1]) && check_quotes2(s, i - 1))))
		j++;
	if (ft_strchr(sep, s[i - 1]) && !check_quotes2(s, i - 1))
		j--;
	return (j);
}

int	ft_fillcount(char const *s, int i, int j)
{
	int	d;
	int	y;
	int	count;

	count = 0;
	d = j - i;
	y = i;
	while (y > 0)
	{
		if (s[d] != '\'' && s[d] != '"')
			count++;
		d++;
		y--;
	}
	return (count);
}

static char	*ft_filldest2(char const *s, int i, int j)
{
	char	*dest;
	int		n;

	n = 0;
	dest = malloc(sizeof(char) * (ft_fillcount(s, i, j) + 1));
	if (!dest)
		return (0);
	j = j - i;
	while (i > 0)
	{
		if (s[j] != '\'' && s[j] != '"')
			dest[n++] = s[j];
		i--;
		j++;
	}
	dest[n] = '\0';
	return (dest);
}

char	**ft_split2(char const *s, char const *sep)
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
			dest[j++] = ft_filldest2(s, i - n, i);
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

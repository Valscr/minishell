/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:36:01 by vescaffr          #+#    #+#             */
/*   Updated: 2023/02/03 00:05:30 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes2(char const *str, int i)
{
	int	j;
	int	y;

	y = 0;
	j = i;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			y++;
			break ;
		}
		i++;
	}
	y += quotes_after(str, j);
	if (y == 2)
		return (1);
	return (0);
}

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
			while (ft_strchr(sep, s[i]) && !check_quotes2(s, i))
				i++;
			j++;
		}
	}
	if (s[0] != '\0' && (!ft_strchr(sep, s[0])
			|| (ft_strchr(sep, s[i]) && check_quotes2(s, i))))
		j++;
	if (ft_strchr(sep, s[i - 1]) && !check_quotes2(s, i - 1))
		j--;
	return (j);
}

static char	*ft_filldest2(char const *s, int i, int j)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:36:33 by valentin          #+#    #+#             */
/*   Updated: 2023/03/11 23:21:40 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*cut_arg(char *str, int j, int i)
{
	char	*dest;
	int		d;

	d = 0;
	if (!str || j - i == 0)
		return (NULL);
	dest = malloc(sizeof(char) * (i - j + 2));
	if (!dest)
		return (NULL);
	while (j < i && str[j] != '\0')
		dest[d++] = str[j++];
	dest[d] = '\0';
	return (dest);
}

int	quotes_after(char const *str, int j)
{
	int	y;

	y = 0;
	while (j >= 0)
	{
		if (str[j] == '\'' || str[j] == '"')
			y++;
		j--;
	}
	return (y);
}

char	*return_word2(char *str, int i)
{
	char	*dest;
	int		j;

	dest = NULL;
	if (!str[i] || str[i] == '\0')
		return (NULL);
	while (str[i] && (str[i] == ' ' || str[i] == '\'' || str[i] == '"'))
		i++;
	j = i;
	if (!str[i] || str[i] == '\0')
		return (NULL);
	while (str[i] != ' ' && str[i] && str[i] != '"'
		&& str[i] != '\'' && str[i] != '$')
		i++;
	dest = cut_arg(str, j, i - 1);
	return (dest);
}

char	*fill_replace_word(char *str3, char *str, int i, int j)
{
	if (i < ft_strlen(str))
	{
		while (str[i])
			str3[j++] = str[i++];
	}
	str3[j] = '\0';
	return (str3);
}

char	*replace_word(t_data *data, char *str, int i, int y)
{
	char	*dest;
	char	*str2;
	char	*str3;
	int		j;

	j = -1;
	str2 = NULL;
	dest = return_word2(str, i + 1);
	if (!dest)
		return (NULL);
	str2 = get_env_list(data->env, dest);
	str3 = malloc(sizeof(char) * (ft_strlen(str2) + ft_strlen(str)
				- ft_strlen(dest) + 1));
	if (!str3)
		return (free(dest), free(str2), NULL);
	while (++j < i)
		str3[j] = str[j];
	while (y < ft_strlen(str2))
		str3[j++] = str2[y++];
	i += ft_strlen(dest) + 1;
	str3 = fill_replace_word(str3, str, i, j);
	return (free_str(dest), free_str(str), free_str(str2), str3);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:36:33 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 15:06:18 by valentin         ###   ########.fr       */
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
	while (j <= i && str[j] != '\0')
		dest[d++] = str[j++];
	dest[d] = '\0';
	return (dest);
}

char	*util_limiter(char **str, t_data *data, char *dest, int i)
{
	while (str[i] && !is_file(str[i])
		&& ft_strncmp(str[i], data->limiter, ft_strlen(data->limiter)))
	{
		dest = ft_strjoin(dest, " ");
		dest = ft_strjoin(dest, str[i]);
		i++;
	}
	free(data->limiter);
	data->limiter = NULL;
	return (dest);
}

int	is_meta(char *str, int i, char c)
{
	if (str[i] == c && check_quotes(str, i))
		return (1);
	else
		return (0);
}

int	quotes_after(char const *str, int j)
{
	int	y;

	y = 0;
	while (j >= 0)
	{
		if (str[j] == '\'' || str[j] == '"')
		{
			y++;
			break ;
		}
		j--;
	}
	return (y);
}

char	*replace_word(t_data *data, char *str, int i)
{
	char	*dest;
	char	*str2;
	char	*str3;
	int		j;
	int		y;

	j = 0;
	y = 0;
	dest = return_word(str, i + 1);
	str2 = get_env_list(data->env, dest);
	str3 = malloc(sizeof(char) * (ft_strlen(str2)
				+ ft_strlen(str) - ft_strlen(dest) + 1));
	while (j < i)
	{
		str3[j] = str[j];
		j++;
	}
	while (y < ft_strlen(str2))
		str3[j++] = str2[y++];
	i += ft_strlen(dest) + 1;
	while (str[i])
		str3[j++] = str[i++];
	str3[j] = '\0';
	return (free_str(dest), free_str(str), free_str(str2), str3);
}

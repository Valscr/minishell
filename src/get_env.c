/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:57:11 by valentin          #+#    #+#             */
/*   Updated: 2023/03/10 21:49:51 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*loop_env(char *dest, t_data *data, int i)
{
	if (!dest)
		return (NULL);
	if (i == 0 && dest[i] == '$' && dest[i + 1] && dest[i + 1] == '?')
		dest = replace_code_error(dest, i);
	else if (i == 0 && dest[i] == '$' && dest[i + 1] && isprint(dest[i + 1]
			&& dest[i + 1] != '\'' && dest[i + 1] != '"')
		&& (!check_quotes1(dest, i, '\'')))
		dest = replace_word(data, dest, i, 0);
	return (dest);
}

char	*get_env(char *str, t_data *data)
{
	int		i;
	char	*dest;

	dest = ft_strdup(str);
	if (!dest)
		return (NULL);
	i = 0;
	while (dest[i])
	{
		if (i > 0 && dest[i] == '?' && dest[i - 1] == '$')
		{
			dest = replace_code_error(dest, i - 1);
			if (i + 1 > ft_strlen(dest))
				break ;
		}
		else if (is_get_env(dest, i))
		{
			dest = replace_word(data, dest, i - 1, 0);
			if (i + 1 > ft_strlen(dest))
				break ;
		}
		dest = loop_env(dest, data, i++);
	}
	return (dest);
}

char	*replace_code_error_bis(char *str, char *dest, char *code_error, int i)
{
	int		j;
	int		y;

	j = 0;
	y = 0;
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	while (y < ft_strlen(code_error))
		dest[j++] = code_error[y++];
	i += 2;
	if (str[i])
	{
		while (str[i])
			dest[j++] = str[i++];
	}
	dest[j] = '\0';
	return (free_str(code_error), free_str(str), dest);
}

char	*replace_code_error(char *str, int i)
{
	char	*dest;
	char	*code_error;

	if (!str)
		return (NULL);
	code_error = ft_itoa(g_sig.code_error);
	dest = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(code_error) - 1));
	if (!dest)
		return (NULL);
	return (replace_code_error_bis(str, dest, code_error, i));
}

char	*get_env_list(t_env *head, char *name)
{
	t_env	*current;

	if (name[0] == '\0')
		return (NULL);
	current = head;
	while (current != NULL)
	{
		if (ft_strncmp(current->value, name, ft_strlen(name)) == 0
			&& current->value[ft_strlen(name)] == '=')
		{
			if (ft_strlen(current->value) < (ft_strlen(name) + 1))
				return (NULL);
			return (ft_strdup(current->value + ft_strlen(name) + 1));
		}
		current = current->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:57:11 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 16:35:03 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*loop_env(char *dest, t_data *data, int i)
{
	if (i == 0 && dest[i] == '$' && dest[i + 1] && dest[i + 1] == '?')
		dest = replace_code_error(dest, i);
	else if (i == 0 && dest[i] == '$' && dest[i + 1] && isprint(dest[i + 1])
		&& (!check_quotes1(dest, i, '\'')))
		dest = replace_word(data, dest, i);
	return (dest);
}

char	*get_env(char *str, t_data *data)
{
	int		i;
	char	*dest;

	if (!str || !str[0])
		return (NULL);
	dest = ft_strdup(str);
	i = 0;
	while (dest[i])
	{
		if (i > 0 && dest[i] == '?' && dest[i - 1] == '$')
		{
			dest = replace_code_error(dest, i - 1);
			if (i + 1 > ft_strlen(dest))
				break ;
		}
		else if (i > 0 && isprint(dest[i]) && dest[i - 1] == '$'
			&& dest[i] != ' ' && (!check_quotes1(dest, i - 1, '\'')))
		{
			dest = replace_word(data, dest, i - 1);
			if (i + 1 > ft_strlen(dest))
				break ;
		}
		dest = loop_env(dest, data, i++);
	}
	return (dest);
}

char	*replace_code_error(char *str, int i)
{
	char	*dest;
	char	*error;
	int		j;
	int		y;

	j = 0;
	y = 0;
	error = ft_itoa(code_error);
	dest = malloc(sizeof(char) * (ft_strlen(str)
				+ ft_strlen(error) - 2 + 1));
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	while (y < ft_strlen(error))
		dest[j++] = error[y++];
	i += 2;
	if (str[i])
	{
		while (str[i])
			dest[j++] = str[i++];
	}
	dest[j] = '\0';
	return (free_str(error), free_str(str), dest);
}

char	*get_env_list(t_env *head, char *name)
{
	t_env	*current;

	current = head;
	while (current->next != NULL)
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

/*void display_env_list(t_env **head)
{
    t_env *current = *head;
	
    while (current != NULL && current->next != NULL)
	{
        printf("%s\n", current->value);
        current = current->next;
    }
	return ;
}*/
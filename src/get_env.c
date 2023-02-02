/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:57:11 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 00:05:49 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (i > 0 && dest[i] == '$' && dest[i - 1] != '$' && dest[i + 1] == '?')
			dest = replace_code_error(dest, i);
		else if (i > 0 && dest[i] == '$' && isprint(dest[i + 1])
			&& dest[i + 1] != ' ' && dest[i - 1] != '$'
			&& (!check_quotes1(dest, i, '\'')))
		{
			dest = replace_word(data, dest, i);
		}
		else if (i == 0 && dest[i] == '$' && dest[i + 1] == '?')
			dest = replace_code_error(dest, i);
		else if (i == 0 && dest[i] == '$' && isprint(dest[i + 1])
			&& (!check_quotes1(dest, i, '\'')))
			dest = replace_word(data, dest, i);
		i++;
	}
	return (dest);
}

char	*get_env_list(t_env *head, char *name)
{
	t_env	*current;

	current = head;
	while (current->next != NULL)
	{
		if (strncmp(current->value, name, strlen(name)) == 0
			&& current->value[strlen(name)] == '=')
		{
			return (ft_strdup(current->value + strlen(name) + 1));
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
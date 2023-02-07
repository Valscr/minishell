/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:50:33 by valentin          #+#    #+#             */
/*   Updated: 2023/02/06 17:42:55 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_list_to_string_array(t_env *head)
{
	int		count;
	t_env	*current;
	char	**str;
	int		i;

	current = head;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	str = malloc(sizeof(char *) * (count + 1));
	current = head;
	i = 0;
	while (current != NULL && current->next != NULL)
	{
		str[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	copy_string_array_to_env_list(t_env **head, char *string_array[])
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (string_array[i])
	{
		name = ft_strdup(string_array[i]);
		value = strchr(name, '=');
		if (value != NULL)
		{
			*value = '\0';
			value++;
			add_env_front(head, name, value);
		}
		free(name);
		i++;
	}
}

void	add_env_front(t_env **head, const char *name, const char *value)
{
	t_env	*new_node;
	char	*str;
	char	*str2;

	str = ft_strjoin(name, "=");
	str2 = ft_strjoin(str, value);
	new_node = (t_env *) malloc(sizeof(t_env));
	new_node->value = ft_strdup(str2);
	new_node->next = NULL;
	ft_lstadd_front((t_list **)head, (t_list *)new_node);
	free(str);
	free(str2);
	return ;
}

void	add_env_back(t_env **head, const char *name, const char *value)
{
	t_env	*new_node;

	new_node = (t_env *) malloc(sizeof(t_env));
	new_node->value = ft_strdup(ft_strjoin(ft_strjoin(name, "="), value));
	new_node->next = NULL;
	ft_lstadd_back((t_list **)head, (t_list *)new_node);
	return ;
}

void	add_env_variable(t_env **head, const char *name, const char *val)
{
	t_env	*current ;
	char	*str;
	char	*str2;

	str = ft_strjoin(name, "=");
	str2 = ft_strjoin(str, val);
	free(str);
	current = *head;
	while (current != NULL && current->next != NULL)
	{
		if (strncmp(current->value, name, strlen(name)) == 0
			&& current->value[strlen(name)] == '=')
		{
			free(current->value);
			current->value = ft_strdup(str2);
			free(str2);
			return ;
		}
		current = current->next;
	}
	add_env_front(head, name, val);
	free(str2);
	return ;
}

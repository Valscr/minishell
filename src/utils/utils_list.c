/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:50:33 by valentin          #+#    #+#             */
/*   Updated: 2023/03/02 00:44:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_list(t_env *env)
{
	int		count;
	t_env	*current;

	current = env;
	count = 0;
	while (current->next != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**env_list_to_string_array(t_env *head)
{
	int		count;
	t_env	*current;
	char	**str;

	count = size_list(head);
	str = malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	current = head;
	count = 0;
	while (current->next != NULL)
	{
		str[count] = ft_strdup(current->next->value);
		if (!str[count])
		{
			free_tab_str(str);
			return (NULL);
		}
		current = current->next;
		count++;
	}
	str[count] = NULL;
	return (str);
}

int	copy_string_array_to_env_list(t_env *head, char *string_array[])
{
	t_env	*new_node;
	int		i;

	i = 0;
	new_node = head;
	while (string_array[i])
	{
		if (!add_first(new_node, string_array[i]))
		{
			free_t_env_list(head);
			return (0);
		}
		new_node = new_node->next;
		i++;
	}
	return (1);
}

int	find_string_in_list(t_env *head, const char *string)
{
	int		len;
	t_env	*cur;
	char	*tmp;

	cur = head;
	tmp = ft_strchr(string, '=');
	if (!tmp)
		return (1);
	len = ft_strlen(string) - ft_strlen(tmp);
	while (cur->next)
	{
		if (ft_strncmp(cur->next->value, string, len) == 0)
		{
			cur->next->value = ft_strdup(string);
			printf("%s\n", cur->next->value);
			fflush(stdout);
			if (!cur->next->value)
				return (-1);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

/*si la fonction rencontre une erreur renvoie 1, sinon renvoie 0*/
int	add_env_variable(t_env *head, char *string)
{
	int	res;

	if (string[0] == '=')
		return (write_perror("export: not a valid identifier"));
	res = find_string_in_list(head, string);
	if (res == -1)
		return (write_perror("Error malloc\n"));
	if (res == 1)
		return (1);
	return (add_last(head, string));
}

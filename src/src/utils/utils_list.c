/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:50:33 by valentin          #+#    #+#             */
/*   Updated: 2023/03/15 20:59:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	find_string_in_list(t_env *head, const char *string, int len)
{
	t_env	*cur;
	char	*tmp;

	cur = head;
	tmp = ft_strchr(string, '=');
	if (!tmp)
		return (1);
	if (!check_quotes(tmp, 0))
		tmp = delete_quotes(tmp);
	len = ft_strlen(string) - ft_strlen(tmp);
	while (cur->next)
	{
		if (ft_strncmp(cur->next->value, string, len)
			== 0 && cur->next->value[len] == '=')
		{
			if (cur->next->value)
				free(cur->next->value);
			cur->next->value = ft_strdup(string);
			if (!cur->next->value)
				return (-1);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

char	*delete_quotes(char *str)
{
	int		i;
	int		j;
	int		d;
	char	*dest;

	j = ft_strlen(str) - 1;
	i = 0;
	d = 0;
	while (str[i] != '=')
		i++;
	while (str[i] == '\'' || str[i] == '\"')
		i++;
	while (str[j] == '\'' || str[j] == '\"')
		j--;
	dest = malloc(sizeof(char) * (j - i) + 1);
	if (!dest)
		return (free_str(str), NULL);
	i++;
	while (i <= j)
		dest[d++] = str[i++];
	dest[d] = '\0';
	return (free_str(str), dest);
}

int	add_env_variable(t_env *head, char *string)
{
	int	res;
	int	i;

	i = 0;
	while (string[i] == ' ')
		i++;
	if (!string[i])
		return (i);
	if (string[i] == '=')
		return (write_perror("export: not a valid identifier"), 0);
	while (string[i] != '=')
		i++;
	res = find_string_in_list(head, string, 0);
	if (res == -1)
		return (write_perror("Error malloc\n"));
	if (res == 1)
		return (1);
	return (add_last(head, string));
}

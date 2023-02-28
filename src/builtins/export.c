/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:48:13 by valentin          #+#    #+#             */
/*   Updated: 2023/02/28 18:13:34 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**new_env(char **envp, char *value, char *name, int i)
{
	char	**dest;
	int		j;

	j = 0;
	dest = malloc(sizeof(char *) * count_tab(envp) + 1);
	if (!dest)
		return (NULL);
	while (j < i)
	{
		dest[j] = ft_strdup(envp[j]);
		j++;
	}
	dest[j++] = ft_strdup(ft_strjoin(ft_strjoin(name, "="), value));
	while (envp[j])
	{
		dest[j] = ft_strdup(envp[j]);
		j++;
	}
	dest[j] = NULL;
	return (dest);
}

int	ft_export(char *name, char *value, t_data *data)
{
	add_env_variable(&data->env, name, value);
	return (0);
}

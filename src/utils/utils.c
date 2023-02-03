/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:10:23 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 01:58:17 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init(t_data	*data, char **envp)
{
	data->infile = 0;
	data->outfile = 0;
	data->file = 0;
	data->count = 0;
	data->redir = 0;
	data->error = 0;
	data->limiter = NULL;
	data->paths = NULL;
	g_sig.pid = 0;
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.code_error = 0;
	data->cmd_paths = NULL;
	data->cmd = NULL;
	data->cmd_redir = NULL;
	data->envp = NULL;
	data->env = (t_env *)malloc(sizeof(t_env));
	data->env->next = NULL;
	copy_string_array_to_env_list(&data->env, envp);
	return ;
}

/*char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}*/

char	*find_path(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (strncmp(current->value, "PATH=", 5) == 0)
		{
			return (current->value + 5);
		}
		current = current->next;
	}
	return (NULL);
}

char	*return_word(char *str, int i)
{
	char	*dest;
	int		j;

	dest = NULL;
	if (!str[i] || str[i] == '\0')
		return (NULL);
	while (str[i] == ' ' && str[i])
		i++;
	j = i;
	if (!str[i] || str[i] == '\0')
		return (NULL);
	while (str[i] != ' ' && str[i] && str[i] != '>' && str[i] != '<'
		&& str[i] != '"' && str[i] != '\'' && str[i] != '$')
		i++;
	dest = cut_arg(str, j, i - 1);
	return (dest);
}

int	is_file(const char *filename)
{
	struct stat	file_stat;

	if (stat(filename, &file_stat) == -1)
		return (0);
	else
		return (1);
}

int	count_tab(char **str)
{
	int	i;

	i = 0;
	if (str[0] == 0)
		return (i);
	while (str[i])
		i++;
	return (i);
}

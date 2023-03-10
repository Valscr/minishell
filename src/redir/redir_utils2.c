/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:03:14 by valentin          #+#    #+#             */
/*   Updated: 2023/03/10 21:59:34 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*return_cmd(char *str, int i)
{
	char	*dest;
	int		j;

	j = i;
	while (str[j] && str[j] != '<' && str[j] != '>')
		j++;
	dest = malloc(sizeof(char) * ((j - i) + 1));
	if (!dest)
		return (NULL);
	j = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		dest[j++] = str[i++];
	if (dest[j - 1] == ' ')
	{
		j--;
		while (dest[j] == ' ')
			j--;
		dest[j + 1] = '\0';
	}
	else
		dest[j] = '\0';
	if (!check_char(dest))
		return (free(dest), NULL);
	return (dest);
}

char	*return_cmd_after(char *str, t_data *data)
{
	int		i;
	char	*dest2;
	char	*dest3;

	i = 0;
	dest2 = NULL;
	dest3 = NULL;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			i = end_word(str, i);
			free(dest3);
			dest3 = NULL;
			if (str[i])
				dest3 = return_word(str, i);
			if (is_cmd(data->cmd_paths, dest3))
			{
				dest2 = return_cmd(str, i);
				break ;
			}
		}
		i++;
	}
	return (free_str(dest3), dest2);
}

char	*new_command(char *str, t_data *data)
{
	int		i;
	char	*dest;
	char	*dest2;

	i = 0;
	dest = return_word(str, i);
	if (!dest)
		return (NULL);
	dest2 = NULL;
	if (is_cmd(data->cmd_paths, dest))
		dest2 = return_cmd(str, i);
	else if (find_cmd_after(str, data))
		dest2 = return_cmd_after(str, data);
	free(dest);
	return (dest2);
}

int	check_file(t_data *data, char *dest)
{
	if (dest == NULL)
		return (0);
	if (data->limiter_error)
		return (0);
	if (is_file(dest) && data->type == 0)
	{
		data->infile = open(dest, O_CLOEXEC | O_RDONLY);
		if (data->infile < 0)
			return (0);
		return (1);
	}
	else if (data->type == 1 && !is_file(dest))
	{
		write_perror(dest);
		return (0);
	}
	else if (data->type == 1 && is_file(dest))
		return (1);
	return (0);
}

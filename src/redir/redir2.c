/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:22:17 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 15:38:24 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_file(char *str, t_data *data, int i, int type)
{
	char	*dest;

	dest = return_word(str, i + 1);
	if (ft_strlen(dest) > 0)
	{
		if (type == 1)
			data->outfile = open(dest, O_APPEND | O_CREAT | O_RDWR, 0644);
		else if (type == 2)
			data->outfile = open(dest, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (data->outfile < 0)
		{
			free_str(dest);
			return (0);
		}
		free_str(dest);
		return (1);
	}
	free_str(dest);
	return (0);
}

int	find_char(char *str, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (check_quotes(str, i))
				j++;
		}
		i++;
	}
	return (j);
}

int	check_redir(char *str)
{
	if (ft_strnstr(str, "<", ft_strlen(str)) && find_char(str, '<'))
		return (1);
	if (ft_strnstr(str, ">", ft_strlen(str)) && find_char(str, '>'))
		return (1);
	if (ft_strnstr(str, "<<", ft_strlen(str)) && find_char(str, '<'))
		return (1);
	if (ft_strnstr(str, ">>", ft_strlen(str)) && find_char(str, '>'))
		return (1);
	return (0);
}

int	init_redir(t_data *data)
{
	int	i;

	data->cmd_redir = malloc(sizeof(char *) * (count_tab(data->cmd) + 1));
	if (!data->cmd_redir)
		return (0);
	i = 0;
	while (i <= (count_tab(data->cmd)))
		data->cmd_redir[i++] = NULL;
	return (1);
}

int	end_word(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '>' || str[i] == '<')
		i++;
	while (str[i] != ' ' && str[i] && str[i] != '>' && str[i] != '<'
		&& str[i] != '"' && str[i] != '\'' && str[i] != '\0')
		i++;
	return (i);
}

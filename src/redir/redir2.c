/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:22:17 by valentin          #+#    #+#             */
/*   Updated: 2023/03/12 03:44:32 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	end_word(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '>' || str[i] == '<')
		i++;
	while (str[i] != ' ' && str[i] && str[i] != '>' && str[i] != '<'
		&& str[i] != '"' && str[i] != '\'' && str[i] != '\0')
		i++;
	return (i);
}

int	open_file(char *str, t_data *data, int i, int type)
{
	char	*dest;

	if (data->type == 1)
		return (1);
	dest = return_word(str, i + 1);
	if (ft_strlen(dest) > 0)
	{
		if (type == 1)
			data->outfile = open(dest, O_CLOEXEC | O_APPEND
					| O_CREAT | O_RDWR, 0644);
		else if (type == 2)
			data->outfile = open(dest, O_CLOEXEC | O_TRUNC
					| O_CREAT | O_RDWR, 0644);
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

int	redir_in(char *str, char *dest, t_data *data, int i)
{
	if (!find_cmd(str, data, 1))
		return (0);
	dest = return_word(str, i + 1);
	if (!dest)
		return (0);
	if (!check_file(data, dest))
	{
		g_sig.code_error = ERROR_FILE;
		if (data->limiter_error)
		{
			g_sig.code_error = SUCESS_CODE;
			data->limiter_error = 0;
		}
		return (free(dest), 0);
	}
	free_str(dest);
	dest = NULL;
	return (1);
}

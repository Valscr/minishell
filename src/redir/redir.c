/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:20:12 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 04:10:17 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pars_redir_in(char *str, t_data *data)
{
	int		i;
	char	*dest;
	int		d;

	i = 0;
	dest = NULL;
	while (str[i])
	{
		if ((i == 0 && is_meta(str, i, '<') && !ft_strchr("<>", str[i + 1]))
			|| (i > 0 && !ft_strchr("<>", str[i - 1]) && is_meta(str, i, '<')
				&& !ft_strchr("<>", str[i + 1])))
		{
			if (!find_cmd(str, data, 1))
				return (0);
			dest = return_word(str, i + 1);
			d = check_file(data, dest);
			if (d == 1)
				return (free(dest), 1);
			else if (d == 2)
				return (free(dest), 0);
			free(dest);
		}
		limiter_heredoc(str, data, i++);
	}
	return (1);
}

int	pars_redir_out(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_meta(str, i, '>') && !ft_strchr("><", str[i + 1]) && i == 0)
		{
			if (!open_file(str, data, i, 2) || !find_cmd(str, data, 0))
				return (0);
		}
		else if (i > 0 && is_meta(str, i, '>') && !ft_strchr("<>", str[i + 1])
			&& !ft_strchr("<>", str[i - 1]))
		{
			if (!open_file(str, data, i, 2) || !find_cmd(str, data, 0))
				return (0);
		}
		if (is_meta(str, i, '>') && is_meta(str, i + 1, '>')
			&& !ft_strchr("<>", str[i + 2]))
		{
			if (!open_file(str, data, i + 1, 1) || !find_cmd(str, data, 0))
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_redir(t_data *d)
{
	int	redir;

	redir = 0;
	if ((ft_strlen(d->cmd[d->count]) <= 2 && (d->cmd[d->count][1] == '>'
			|| d->cmd[d->count][1] == '<')) || ft_strlen(d->cmd[d->count]) <= 1)
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		exit(1);
	}
	if (ft_strnstr(d->cmd[d->count], "<", ft_strlen(d->cmd[d->count])))
	{
		if (!pars_redir_in(d->cmd[d->count], d))
			exit(1);
		redir = 1;
	}
	if (ft_strnstr(d->cmd[d->count], ">", ft_strlen(d->cmd[d->count])))
	{
		if (!pars_redir_out(d->cmd[d->count], d))
			exit (1);
		redir += 2;
	}
	d->cmd_redir[d->count] = new_command(d->cmd[d->count], d);
	return (redir);
}

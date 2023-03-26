/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:20:12 by valentin          #+#    #+#             */
/*   Updated: 2023/03/24 11:24:40 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	err_syntax(char *str, t_data *data, int i)
{
	if (str[i] == '\0' || str[i + 1] == '\0')
	{
		if (data->type)
			write(STDERR, "syntax error\n", 14);
		g_sig.code_error = ERROR_SYNTAX;
		return (0);
	}
	return (1);
}

int	pars_redir_in(char *str, t_data *data, int i)
{
	char	*dest;

	dest = NULL;
	while (str[++i])
	{
		if ((i == 0 && is_meta(str, i, '<') && !ft_strchr("<>", str[i + 1]))
			|| (i > 0 && !ft_strchr("<>", str[i - 1]) && is_meta(str, i, '<')
				&& (!ft_strchr("<>", str[i + 1]) || str[i + 1] == '\0')))
			if (!err_syntax(str, data, i + 1) || !redir_in(str, dest, data, i))
				return (0);
		if (is_here(i, str))
		{
			if (!err_syntax(str, data, i + 2))
				return (0);
			data->limiter_error = 1;
			if (data->limiter == 1 && data->type == 0)
				return (open_here_doc(data), redir_in(str, dest, data, i),
					free_str(dest), 1);
			else
				return (redir_in(str, dest, data, i), free_str(dest), 0);
		}
	}
	return (free_str(dest), 1);
}

int	pars_redir_out(char *str, t_data *data, int i)
{
	while (str[i])
	{
		if (is_meta(str, i, '>') && !ft_strchr("><", str[i + 1]) && i == 0)
		{
			if (!open_file(str, data, i, 2) || !find_cmd(str, data, 0))
				return (0);
		}
		else if (i > 0 && is_meta(str, i, '>') && (!ft_strchr("<>", str[i + 1])
				|| str[i + 1] == '\0') && !ft_strchr("<>", str[i - 1]))
		{
			if (!err_syntax(str, data, i + 1) || !open_file(str, data, i, 2)
				|| !find_cmd(str, data, 0))
				return (0);
		}
		if (is_meta(str, i, '>') && is_meta(str, i + 1, '>')
			&& (!ft_strchr("<>", str[i + 2]) || str[i + 2] == '\0'))
		{
			if (!err_syntax(str, data, i + 2) || !open_file(str, data, i + 1, 1)
				|| !find_cmd(str, data, 0))
				return (0);
		}
		i++;
	}
	return (1);
}

void	ft_redir_bis(t_data *data, char *cmd)
{	
	data->cmd_redir = NULL;
	if (data->type == 0)
		data->cmd_redir = new_command(cmd, data);
	return ;
}

int	ft_redir(t_data *d, char *cmd)
{
	int	redir;

	redir = 0;
	if (!cmd)
		return (-1);
	if ((ft_strlen(cmd) <= 2 && (cmd[1] == '>' || cmd[1] == '<'))
		|| ft_strlen(cmd) <= 1 || check_redir_error(cmd))
		return (error_syntax(d), -1);
	if (ft_strnstr(cmd, "<", ft_strlen(cmd)))
	{
		if (!pars_redir_in(cmd, d, -1))
			return (-1);
		redir = 1;
	}
	if (ft_strnstr(cmd, ">", ft_strlen(cmd)))
	{
		if (!pars_redir_out(cmd, d, 0))
			return (-1);
		redir += 2;
	}
	return (ft_redir_bis(d, cmd), redir);
}

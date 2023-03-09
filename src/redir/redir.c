/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:20:12 by valentin          #+#    #+#             */
/*   Updated: 2023/03/09 19:42:01 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_in(char *str, char *dest, t_data *data, int i)
{
	printf("redirin\n");
	if (!find_cmd(str, data, 1))
		return (0);
	dest = return_word(str, i + 1);
	if (!dest)
		return (write_perror("Error malloc\n"));
	if (!check_file(data, dest))
	{
		g_sig.code_error = ERROR_FILE;
		if (data->limiter_error)
		{
			g_sig.code_error = 0;
			data->limiter_error = 0;
		}
		return (free(dest), 0);
	}
	free_str(dest);
	dest = NULL;
	return (1);
}

int	pars_redir_in(char *str, t_data *data)
{
	int		i;
	char	*dest;

	i = -1;
	dest = NULL;
	while (str[++i])
	{
		if ((i == 0 && is_meta(str, i, '<') && !ft_strchr("<>", str[i + 1]))
			|| (i > 0 && !ft_strchr("<>", str[i - 1]) && is_meta(str, i, '<')
				&& !ft_strchr("<>", str[i + 1])))
			if (!redir_in(str, dest, data, i))
				return (0);
		if (is_meta(str, i, '<') && is_meta(str, i + 1, '<')
			&& !ft_strchr("<>", str[i + 2]))
		{
			data->limiter_error = 1;
			if (data->limiter == 1 && data->type == 0)
				return (redir_in(str, dest, data, i),
					open_here_doc(data), free_str(dest), 1);
			else
				return (redir_in(str, dest, data, i), free_str(dest), 0);
		}
	}
	return (free_str(dest), 1);
}

int	pars_redir_out(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_meta(str, i, '>') && !ft_strchr("><", str[i + 1]) && i == 0)
		{
			if (!find_cmd(str, data, 0) || !open_file(str, data, i, 2))
				return (0);
		}
		else if (i > 0 && is_meta(str, i, '>') && !ft_strchr("<>", str[i + 1])
			&& !ft_strchr("<>", str[i - 1]))
		{
			if (!find_cmd(str, data, 0) || !open_file(str, data, i, 2))
				return (0);
		}
		if (is_meta(str, i, '>') && is_meta(str, i + 1, '>')
			&& !ft_strchr("<>", str[i + 2]))
		{
			if (!find_cmd(str, data, 0) || !open_file(str, data, i + 1, 1))
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
		|| ft_strlen(cmd) <= 1)
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		g_sig.code_error = 2;
		return (-1);
	}
	if (ft_strnstr(cmd, "<", ft_strlen(cmd)))
	{
		if (!pars_redir_in(cmd, d))
			return (-1);
		redir = 1;
	}
	if (ft_strnstr(cmd, ">", ft_strlen(cmd)))
	{
		if (!pars_redir_out(cmd, d))
			return (-1);
		redir += 2;
	}
	return (ft_redir_bis(d, cmd), redir);
}

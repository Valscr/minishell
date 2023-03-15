/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:16:58 by valentin          #+#    #+#             */
/*   Updated: 2023/03/15 20:33:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_arg_bis(char *str, t_data *data)
{
	if ((!ft_strncmp("pwd", str, 3) && ft_strlen(str) == 3)
		|| (!ft_strncmp("pwd", str, 3) && str[3] == ' '))
	{
		ft_pwd();
		free_end_process(data);
		exit(0);
	}
	if (!ft_strncmp("cd", str, 2) || !ft_strncmp("export", str, 6)
		|| !ft_strncmp("unset", str, 5) || !ft_strncmp("exit", str, 4))
	{
		free_end_process(data);
		exit(0);
	}
	return (0);
}

int	check_arg(char *str, t_data *data)
{
	int		end;

	end = 0;
	if (!ft_strncmp("env", str, 3) && (str[3] == ' ' || str[3] == '\0'))
	{
		end = display_env_list(data->env);
		free_end_process(data);
		exit(end);
	}
	if (!ft_strncmp("echo", str, 4))
	{
		if (str[4] != ' ')
		{
			g_sig.code_error = ERROR_NOTFOUND;
			return (0);
		}
		str += 5;
		end = ft_echo(str);
		free_end_process(data);
		exit(end);
	}
	return (check_arg_bis(str, data));
}

int	check_arg2(char *str, t_data *data)
{
	char	**dest;
	char	**strg;

	dest = NULL;
	if (!ft_strncmp("cd", str, 2) && (str[2] == ' ' || str[2] == '\0'))
	{
		strg = ft_split(str, " '\"");
		g_sig.code_error = ft_cd(strg, data->env);
		free_tab_str(strg);
	}
	else if (!ft_strncmp("export", str, 6))
	{
		str += 6;
		if (str[0] == ' ' && str[1])
			ft_export(str, data);
		else
			print_sorted_env(data->env);
	}
	else if (!ft_strncmp("unset", str, 5))
	{
		dest = ft_split(str, " ");
		if (dest[1])
			g_sig.code_error = ft_unset(dest[1], data->env);
	}
	return (free_tab_str(dest), 0);
}

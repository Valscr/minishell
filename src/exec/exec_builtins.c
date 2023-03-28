/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:16:58 by valentin          #+#    #+#             */
/*   Updated: 2023/03/28 04:05:22 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_arg(char **str)
{
	if (!ft_strncmp("cd", str[0], 2) || (!ft_strncmp("export", str[0], 6)
			&& str[0][6] == '\0') || (!ft_strncmp("unset", str[0], 5)
		&& str[0][5] == '\0') || (!ft_strncmp("exit", str[0], 4)
		&& str[0][4] == '\0'))
	{
		return (1);
	}
	return (0);
}

int	check_arg_bis(char **str, t_data *data, int end)
{
	if (!ft_strncmp("env", str[0], 3) && str[0][3] == '\0' && !str[1])
	{
		end = display_env_list(data->env);
		free_end_process(data);
		free_tab_str(str);
		exit(end);
	}
	if ((!ft_strncmp("pwd", str[0], 3) && ft_strlen(str[0]) == 3)
		|| (!ft_strncmp("pwd", str[0], 3) && str[0][3] == ' '))
	{
		ft_pwd();
		free_end_process(data);
		free_tab_str(str);
		exit(0);
	}
	if (is_arg(str))
	{
		if (!ft_strncmp("export", str[0], 6) && !str[1])
			print_sorted_env(data->env);
		free_end_process(data);
		free_tab_str(str);
		exit(g_sig.code_error);
	}
	return (free_tab_str(str), 0);
}

int	check_arg(char *str, t_data *data)
{
	int		end;
	char	**dest;

	end = 0;
	dest = ft_split(str, " ");
	take_away_quotes(dest[0]);
	if (!ft_strncmp("echo", dest[0], 4))
	{
		if (dest[0][4] != ' ')
		{
			g_sig.code_error = ERROR_NOTFOUND;
			return (free_tab_str(dest), 0);
		}
		end = ft_echo(str);
		free_end_process(data);
		free_tab_str(dest);
		exit(end);
	}
	return (check_arg_bis(dest, data, end));
}

int	check_arg2bis(char **str, char *string, t_data *data, int count)
{	
	if (!ft_strncmp("cd", str[0], 2) && str[0][2] == '\0')
		g_sig.code_error = ft_cd(str, string, data->env, count);
	return (free_tab_str(str), 0);
}

int	check_arg2(char *string, t_data *data, int count)
{
	char	**str;

	str = ft_split(string, " ");
	take_away_quotes(str[0]);
	if (!ft_strncmp("export", str[0], 6)
		&& str[0][6] == '\0')
	{
		if (str[1])
			g_sig.code_error = ft_export(string, data, count);
	}
	if (!ft_strncmp("unset", str[0], 5) && str[0][5] == '\0' && count == 1)
	{
		if (str[1])
			g_sig.code_error = ft_unset(string, str[1], data->env);
	}
	return (check_arg2bis(str, string, data, count));
}

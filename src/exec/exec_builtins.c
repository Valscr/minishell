/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:16:58 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 02:59:31 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_arg(char *str, t_data *data)
{
	char	**strg;
	int		end;

	end = 0;
	strg = ft_split(str, " '\"");
	if (!ft_strncmp("echo", str, 4))
	{
		end = ft_echo(strg);
		free_tab_str(strg);
		free_end_process(data);
		exit(end);
	}
	if (!ft_strncmp("cd", str, 2))
	{
		end = ft_cd(strg);
		free_tab_str(strg);
		free_end_process(data);
		exit(end);
	}
	if (!ft_strncmp("pwd", str, 3))
	{
		ft_pwd();
		free_tab_str(strg);
		free_end_process(data);
		exit(0);
	}
	/*if (!ft_strncmp("unset", str, 5))
	{
		exit (0);
	}
	if (!ft_strncmp("env", str, 3))
	{
		exit (0);
	}*/
	free_tab_str(strg);
	return (0);
}

int	check_arg2(char *str, t_data *data)
{
	char	**dest;

	dest = ft_split(str, " =");
	if (!ft_strncmp("export", str, 6))
	{
		ft_export(dest[1], dest[2], data);
		return (free_tab_str(dest), 1);
	}
	free_tab_str(dest);
	return (0);
}

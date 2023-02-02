/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:16:58 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 00:04:40 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_arg(char *str)
{
	char	**strg;
	int		end;

	end = 0;
	strg = ft_split(str, " '\"");
	if (!ft_strncmp("echo", str, 4))
	{	
		end = ft_echo(strg);
		free_tab_str(strg);
		exit(end);
	}
	if (!ft_strncmp("cd", str, 2))
	{
		end = ft_cd(strg);
		free_tab_str(strg);
		exit(end);
	}
	if (!ft_strncmp("pwd", str, 3))
	{
		free_tab_str(strg);
		exit(ft_pwd());
	}
	if (!ft_strncmp("export", str, 6))
	{
		free_tab_str(strg);
		exit (0);
	}
	/*if (!ft_strncmp("unset", str, 5))
	{
		return (1);
	}
	if (!ft_strncmp("env", str, 3))
	{
		return (1);
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
		free_tab_str(dest);
		return (1);
	}
	free_tab_str(dest);
	return (0);
}

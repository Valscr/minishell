/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:14:13 by valentin          #+#    #+#             */
/*   Updated: 2023/02/27 16:02:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**search_home(t_env *env)
{
	char	**splt;
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strncmp(cur->value, "HOME=", 5) == 0)
		{
			splt = ft_split(cur->value, "=");
			return (splt);
		}
		cur = cur->next;
	}
	return (NULL);
}

int	ft_cd(char **cmd_tab, t_env *env)
{
	char	cwd[PATH_MAX];
	char	*str;
	char	**splt;	

	if (!cmd_tab[1])
	{
		splt = search_home(env);
		if (!splt)
			return (write_perror("HOME not set\n"));
		chdir(splt[1]);
		free_tab_str(splt);
		return (0);
	}
	if (chdir(cmd_tab[1]) == -1)
	{
		str = ft_strjoin(getcwd(cwd, PATH_MAX), "/");
		if (!str)
			return (perror("Error malloc\n"), 1);
		str = ft_strjoin(str, cmd_tab[1]);
		if (!str)
			return (perror("Error malloc\n"), 1);
		if (chdir(str) != 0)
		{
			free(str);
			return (perror(cmd_tab[1]), 1);
		}
		free(str);
		return (0);
	}
	return (0);
}

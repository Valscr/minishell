/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:14:13 by valentin          #+#    #+#             */
/*   Updated: 2023/02/28 17:34:33 by valentin         ###   ########.fr       */
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
	char	*str2;
	char	**splt;	

	if (!cmd_tab[1])
	{
		splt = search_home(env);
		if (!splt)
			return (write_perror("HOME not set\n"));
		return (chdir(splt[1]), free_tab_str(splt), 0);
	}
	if (chdir(cmd_tab[1]) == -1)
	{
		str = ft_strjoin(getcwd(cwd, PATH_MAX), "/");
		if (!str)
			return (perror("Error malloc\n"), 1);
		str2 = ft_strjoin(str, cmd_tab[1]);
		if (!str2)
			return (free(str), perror("Error malloc\n"), 1);
		if (chdir(str2) != 0)
			return (free(str), free(str2), perror(cmd_tab[1]), 1);
		return (free(str), free(str2), 0);
	}
	return (0);
}

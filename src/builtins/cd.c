/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:14:13 by valentin          #+#    #+#             */
/*   Updated: 2023/03/28 05:04:31 by valentin         ###   ########.fr       */
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

int	cd_alone(t_env *env, int count)
{
	char	**splt;

	splt = search_home(env);
	if (!splt)
		return (write_error("cd: HOME not set\n"));
	if (count == 1)
		return (chdir(splt[1]), free_tab_str(splt), 0);
	return (free_tab_str(splt), 0);
}

int	ft_cd2(char **cmd_tab, int count)
{
	char	*str2;
	char	*str;
	char	cwd[PATH_MAX];

	take_away_quotes(cmd_tab[1]);
	str = ft_strjoin(getcwd(cwd, PATH_MAX), "/");
	if (!str)
		return (1);
	str2 = ft_strjoin(str, cmd_tab[1]);
	if (!str2)
		return (free(str), 1);
	if (access(str2, F_OK) == 0)
	{
		if (count == 1 && chdir(str2) != 0)
			return (free(str), free(str2), perror(cmd_tab[1]), 1);
		return (free(str), free(str2), 0);
	}
	return (free(str), free(str2), perror(cmd_tab[1]), ERROR_FILE);
}

int	ft_cd(char **cmd_tab, char *string, t_env *env, int count)
{
	int		i;

	i = 0;
	if (!cmd_tab[1])
		return (cd_alone(env, count));
	while (string[i] != ' ' && string[i])
		i++;
	if (chdir(cmd_tab[1]) == -1 && check_quotes(string, i))
		return (ft_cd2(cmd_tab, count));
	if (!check_quotes(string, i))
		return (take_away_quotes(string), write_error(string),
			write_error(": command not found\n"), ERROR_NOTFOUND);
	return (0);
}
